#include <filesystem>
#include <fstream>
#include <sstream>

#include "ZiaConfig.hpp"
#include "zia.hpp"
#include "trace.hpp"
#include <openssl/ssl.h>

namespace zia {

bool ConfigServer::verifLine(const std::string &line) noexcept
{
  size_t n = line.find(": ");

  if (n == std::string::npos) {
    return false;
  }
  return true;
}

bool ConfigServer::getConfigFile(const std::string &filename) noexcept
{
  std::ifstream file(filename, std::ios::in);
  if (!file.is_open())
    return false;
  _objects.clear();
  std::string line;
  while (getline(file, line)) {
    if (verifLine(line) == true) {
      std::istringstream is(line);
      std::string key;
      is >> key;
      key.pop_back();
      dems::config::ConfigValue value;
      if (_configMap.find(key) != _configMap.end()) {
        std::string var;
        std::getline(is, var);
        value.v = std::move(var);
        _objects.insert(std::pair<std::string, dems::config::ConfigValue>(key, value));
        _configMap[key]();
      }
    }
  }
  file.close();
  return true;
}

void ConfigServer::setPort() const noexcept
{
  dems::config::ConfigValue value = _objects.at("ports");
  std::istringstream is(std::get<std::string>(value.v));
  const auto ports = _ziaServer.getRunningPorts();
  std::vector<uint16_t> newPorts;
  uint16_t port;

  while (is >> port) {
    newPorts.push_back(port);
  }
  for (auto &&i : ports) {
    if (std::find(newPorts.begin(), newPorts.end(), i) == newPorts.end()) {
      _ziaServer.delRunningPort(i);
    }
  }
  for (auto &&i : newPorts) {
    if (std::find(ports.begin(), ports.end(), i) == ports.end()) {
      _ziaServer.addRunningPort(i);
    }
  }
}

void ConfigServer::setModulesPath() const noexcept
{
  dems::config::ConfigValue value = _objects.at("modules-path");
  std::istringstream is(std::get<std::string>(value.v));
  const auto existing = _ziaServer.getTrackedEntries();
  std::vector<std::string> newPaths;
  std::string modulePath;

  while (is >> modulePath) {
    newPaths.push_back(modulePath);
  }
  for (auto &&i : existing) {
    if (std::filesystem::is_directory(i.string())
        && std::find(newPaths.begin(), newPaths.end(), i) == newPaths.end()) {
      _ziaServer.delModuleDirectory(i);
    }
  }
  for (auto &&i : newPaths) {
    if (std::find(existing.begin(), existing.end(), i) == existing.end()) {
      _ziaServer.addModuleDirectory(i);
    }
  }
}

void ConfigServer::setClients() const noexcept
{
  dems::config::ConfigValue value = _objects.at("max-clients");
  std::istringstream converter(std::get<std::string>(value.v));
  size_t maxClients = 0;

  converter >> maxClients;
  if (_ziaServer.maxClients() != maxClients) {
    _ziaServer.maxClients(maxClients);
  }
}

void ConfigServer::setWatcherDelay() const noexcept
{
  dems::config::ConfigValue value = _objects.at("watcher-delay");
  std::istringstream converter(std::get<std::string>(value.v));
  uint64_t delay;

  if (converter >> delay && delay != _ziaServer.watcherDelay()) {
    _ziaServer.watcherDelay(delay);
  }
}

void ConfigServer::setPollTimeout() const noexcept
{
  dems::config::ConfigValue value = _objects.at("poll-timeout");
  std::istringstream converter(std::get<std::string>(value.v));
  int timeout;

  if (converter >> timeout) {
    _ziaServer.pollTimeout(timeout);
  }
}

ConfigServer::ConfigServer(Server &server) noexcept
        : _ziaServer(server)
{
  _configMap["ports"] =
          ConfigEntry(std::bind(&ConfigServer::setPort, this), std::to_string(zia::DEFAULT_PORT),
                      "The TCP port(s) the server should listen on");
  _configMap["max-clients"] = ConfigEntry(std::bind(&ConfigServer::setClients, this),
                                          std::to_string(zia::DEFAULT_MAX_CLIENTS),
                                          "The maximum number of clients allowed on the server.");
  _configMap["modules-path"] = ConfigEntry(
          std::bind(&ConfigServer::setModulesPath, this), zia::DEFAULT_MODULE_PATH,
          "The folder(s) that will be tracked to load the modules (can be a single file).");
  _configMap["watcher-delay"] = ConfigEntry(std::bind(&ConfigServer::setWatcherDelay, this),
                                            std::to_string(zia::DEFAULT_WATCHER_DELAY),
                                            "The delay (in milliseconds) to wait between two "
                                            "updates of the <modules-path> folder(s).");
  _configMap["poll-timeout"] = ConfigEntry(
          std::bind(&ConfigServer::setPollTimeout, this), std::to_string(zia::DEFAULT_POLL_TIMEOUT),
          "The time to (in milliseconds) wait between two incoming data reception from clients (a "
          "blocking state can be set with a negative value).");
}

bool ConfigServer::createConfigFileAt(const std::string &filename) noexcept
{
  std::ofstream file(filename);

  if (!file.is_open())
    return false;
  file << "#Multiple configuration options should be separated by spaces." << std::endl
       << "#The server updates itself automaticaly with the new values, and, if needed, deletes "
          "the previous ones."
       << std::endl
       << std::endl;
  for (auto &&i : _configMap) {
    file << "#" << i.second.help() << std::endl
         << "#" << i.first << ": " << i.second.defaultValue() << std::endl
         << std::endl;
  }
  file.close();
  return true;
}

} // namespace zia