#pragma once

#include <thread>
#include <mutex>

#include "Client.hpp"
#include "Poll.hpp"
#include "SharedModules.hpp"

namespace zia {
class Server;
}
namespace linet {
class ServerTCP {
public:
  bool update(int timeout, zia::Server &server) noexcept;
  bool eject(int fd) noexcept;
  bool addListener(uint16_t port, int backlog) noexcept;
  bool addListener(uint16_t port) noexcept;
  bool delListener(uint16_t port) noexcept;
  bool setBacklog(uint16_t port, int newBacklog) noexcept;
  bool setBacklog(int newBacklog) noexcept;
  std::vector<uint16_t> getRunningPorts() const noexcept;
  uint16_t getLastPort() const noexcept;
  const std::unordered_map<int, Client> &getClients() const noexcept;

private:
  std::vector<Socket> _listeners;
  std::unordered_map<int, Client> _clients;
  std::mutex _pollMutex;
  Poll _poll;
  bool isRunning : 1;
};
} // namespace linet
