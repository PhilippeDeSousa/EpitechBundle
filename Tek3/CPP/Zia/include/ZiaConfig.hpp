#pragma once

#include <functional>
#include <unordered_map>

#include "Config.hpp"

namespace zia {
class Server;
class ConfigEntry {
public:
  ConfigEntry(std::function<void()> &&confCallback, const std::string &defaultValueStr = "",
              const std::string &help = "")
          : _callback(confCallback)
          , _defaultValueStr(defaultValueStr)
          , _help(help)
  {
  }
  ConfigEntry() = default;
  void operator()() const
  {
    _callback();
  }
  const std::string &defaultValue() const noexcept
  {
    return _defaultValueStr;
  }
  const std::string &help() const noexcept
  {
    return _help;
  }

private:
  std::function<void()> _callback;
  std::string _defaultValueStr;
  std::string _help;
};

class ConfigServer {
public:
  ConfigServer(Server &server) noexcept;
  ~ConfigServer() noexcept = default;
  bool getConfigFile(const std::string &filename) noexcept;
  bool createConfigFileAt(const std::string &filename) noexcept;
  bool verifLine(const std::string &line) noexcept;
  void setPort() const noexcept;
  void setClients() const noexcept;
  void setModulesPath() const noexcept;
  void setWatcherDelay() const noexcept;
  void setPollTimeout() const noexcept;

private:
  Server &_ziaServer;
  dems::config::ConfigObject _objects;
  std::unordered_map<std::string, ConfigEntry> _configMap;
};
} // namespace zia
