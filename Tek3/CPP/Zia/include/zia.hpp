#pragma once

#include <string>
#include <vector>
#include <functional>
#include <fstream>

#include "lserver.hpp"
#include "ZiaConfig.hpp"
#include "folderWatcher.hpp"
#include "discordAPI.hpp"

namespace zia {
class Server {
public:
  Server() noexcept;
  ~Server() noexcept = default;
  bool addRunningPort(uint16_t port) noexcept;
  bool delRunningPort(uint16_t port) noexcept;
  std::vector<uint16_t> getRunningPorts() const noexcept;
  bool addModuleDirectory(const std::string &dir) noexcept;
  bool delModuleDirectory(const std::string &dir) noexcept;
  void configFilePath(const std::string &filepath) noexcept;
  const std::string &configFilePath() const noexcept;
  std::size_t maxClients() const noexcept;
  void maxClients(std::size_t max) noexcept;
  void watcherDelay(uint64_t delay) noexcept;
  uint64_t watcherDelay() const noexcept;
  int pollTimeout() const noexcept;
  void pollTimeout(int newTimeout) noexcept;
  const std::vector<Folder> &getTrackedEntries() const noexcept;
  void updateDiscord() noexcept;
  void runContext(dems::Context &ctx) noexcept;
  int run() noexcept;

private:
  bool verifyConfigFile() noexcept;
  void configFileModified(const std::string &filepath);
  bool reloadConfigFromFile() noexcept;
  void onFileCreated(const std::string &filepath);
  void onFileModified(const std::string &filepath);
  void onFileDeleted(const std::string &filepath);
  zia::SharedModules _modules;
  ConfigServer _configurer;
  linet::ServerTCP _tcpServer;
  FolderWatcher _watcher;
  DiscordAPI _discord;
  std::string _configFilePath;
  std::size_t _maxClients;
  int _pollTimeout;
  bool _isRunning : 1;
};
} // namespace zia
