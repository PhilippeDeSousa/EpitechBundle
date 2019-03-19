#include <algorithm>
#include <filesystem>
#include <sstream>

#include "trace.hpp"
#include "defaultConf.hpp"
#include "zia.hpp"

#define ZIA_NAME "[" BOLDBLUE "Zia" RESET "] "

namespace zia {
Server::Server() noexcept
        : _configurer(*this)
        , _watcher(100)
        , _discord("552217160492253197")
        , _configFilePath(DEFAULT_CONFIG_FILEPATH)
        , _maxClients(DEFAULT_MAX_CLIENTS)
        , _pollTimeout(DEFAULT_POLL_TIMEOUT)
{
}

bool Server::addRunningPort(uint16_t port) noexcept
{
  bool status = _tcpServer.addListener(port);

  if (port == 0 && status == true)
    port = _tcpServer.getLastPort();
  trace(status, ZIA_NAME GREENPLUS "listener on %s%u%s\n", BOLDYELLOW, port, RESET);
  return status;
}

bool Server::delRunningPort(uint16_t port) noexcept
{
  bool status = _tcpServer.delListener(port);

  trace(status, ZIA_NAME REDSUB "listener on %s%u%s\n", BOLDYELLOW, port, RESET);
  return status;
}

std::vector<uint16_t> Server::getRunningPorts() const noexcept
{
  return _tcpServer.getRunningPorts();
}

uint64_t Server::watcherDelay() const noexcept
{
  return _watcher.delay();
}

const std::vector<Folder> &Server::getTrackedEntries() const noexcept
{
  return _watcher.getTrackedEntries();
}

int Server::pollTimeout() const noexcept
{
  return _pollTimeout;
}

void Server::pollTimeout(int newTimeout) noexcept
{
  _pollTimeout = newTimeout;
  if (_pollTimeout > 0)
    trace(true, ZIA_NAME CYANMOD "PollTimeout: %s%d%s millisecond(s)\n", BOLDYELLOW, _pollTimeout,
          RESET);
  else
    trace(true, ZIA_NAME CYANMOD "PollTimeout: %sblocking timeout%s\n", BOLDYELLOW, RESET);
}

void Server::onFileCreated(const std::string &filepath)
{
  _modules.loadOneModule(filepath);
  bool status = _modules.isLoaded(filepath);
  trace(status, ZIA_NAME GREENPLUS "Loading module at: %s%s%s\n", BOLDYELLOW, filepath.c_str(),
        RESET);
}

void Server::onFileModified(const std::string &filepath)
{
  _modules.unloadModule(filepath);
  _modules.loadOneModule(filepath);
  bool status = _modules.isLoaded(filepath);
  trace(status, ZIA_NAME CYANMOD "Reloading module at: %s%s%s\n", BOLDYELLOW, filepath.c_str(),
        RESET);
}

void Server::onFileDeleted(const std::string &filepath)
{
  _modules.unloadModule(filepath);
  bool status = _modules.isLoaded(filepath);
  trace(!status, ZIA_NAME REDSUB "Unloading module at: %s%s%s\n", BOLDYELLOW, filepath.c_str(),
        RESET);
}

bool Server::addModuleDirectory(const std::string &dir) noexcept
{
  bool status = _watcher.track(dir, std::bind(&Server::onFileCreated, this, std::placeholders::_1),
                               std::bind(&Server::onFileModified, this, std::placeholders::_1),
                               std::bind(&Server::onFileDeleted, this, std::placeholders::_1));

  trace(status, ZIA_NAME GREENPLUS "tracking %s%s%s\n", BOLDYELLOW, dir.c_str(), RESET);
  return status;
}

bool Server::delModuleDirectory(const std::string &dir) noexcept
{
  bool status = _watcher.untrack(dir);

  trace(status, ZIA_NAME REDSUB "untracking %s%s%s\n", BOLDYELLOW, dir.c_str(), RESET);
  return status;
}

bool Server::reloadConfigFromFile() noexcept
{
  bool status = _configurer.getConfigFile(_configFilePath);

  trace(status, ZIA_NAME CYANMOD "Configuration updated from %s%s%s\n", BOLDYELLOW,
        _configFilePath.c_str(), RESET);
  return status;
}

bool Server::verifyConfigFile() noexcept
{
  bool status = false;

  if (std::filesystem::is_regular_file(_configFilePath))
    status = true;
  else {
    status = _configurer.createConfigFileAt(_configFilePath);
    trace(status, ZIA_NAME GREENPLUS "Generating generic %s%s%s default configuration file\n",
          BOLDYELLOW, _configFilePath.c_str(), RESET);
  }
  trace(status, ZIA_NAME CYANMOD "Setting configuration file to: %s%s%s\n", BOLDYELLOW,
        _configFilePath.c_str(), RESET);
  return status;
}

void Server::configFilePath(const std::string &filepath) noexcept
{
  _configFilePath = filepath;
}

const std::string &Server::configFilePath() const noexcept
{
  return _configFilePath;
}

std::size_t Server::maxClients() const noexcept
{
  return _maxClients;
}

void Server::maxClients(std::size_t max) noexcept
{
  trace(true, ZIA_NAME CYANMOD "max-clients set to %s%zu%s\n", BOLDYELLOW, max, RESET);
  _maxClients = max;
}

void Server::watcherDelay(uint64_t delay) noexcept
{
  trace(true, ZIA_NAME CYANMOD "watcher-delay set to %s%zu%s\n", BOLDYELLOW, delay, RESET);
  _watcher.delay(delay);
}

void Server::updateDiscord() noexcept
{
  auto ports = getRunningPorts();
  std::stringstream ss;
  if (ports.size() == 0) {
    ss << "Not running on any port.";
  }
  else {
    ss << "Running on: ";
    for (auto &&i : ports) {
      ss << i << " ";
    }
  }
  _discord.setDetails(ss.str());
  ss.str(std::string("Clients: "));
  ss << _tcpServer.getClients().size() << " / " << _maxClients;
  _discord.setState(ss.str());
  _discord.setLargeImageKey("server");
  _discord.setSmallImageKey("pierre");
  _discord.update();
}

void Server::runContext(dems::Context &ctx) noexcept
{
  _modules.runModulesOnCtx(ctx);
}

void Server::configFileModified(const std::string &filepath)
{
  (void)filepath;
  reloadConfigFromFile();
  updateDiscord();
}

int Server::run() noexcept
{
  _discord.startTimer();
  verifyConfigFile();
  _watcher.track(_configFilePath,
                 std::bind(&Server::configFileModified, this, std::placeholders::_1),
                 std::bind(&Server::configFileModified, this, std::placeholders::_1),
                 [](const std::string &) {});
  _watcher.start();
  while (true) {
    size_t nb = _tcpServer.getClients().size();
    _tcpServer.update(_pollTimeout, *this);
    if (nb != _tcpServer.getClients().size())
      updateDiscord();
  }
  _watcher.stop();
  return 0;
}
} // namespace zia
