#pragma once

#ifdef __linux__
#  include <arpa/inet.h>
#elif _WIN32
#  include <Winsock2.h>
#endif

#include <string>

namespace linet {
const uint16_t AUTO_PORT = 0;
const int DEFAULT_BACKLOG = 1 << 8;
class Socket {
public:
#ifdef __linux__
  Socket() = default;
#elif _WIN32
  Socket() noexcept;
#endif
  Socket(uint16_t port, int backlog = DEFAULT_BACKLOG) noexcept;
  ~Socket() = default;
  Socket &operator=(const Socket &other);
  const std::string &getIpv4() const noexcept;
  uint16_t getPort() const noexcept;
  int getBacklog() const noexcept;
  int getFdHandle() const noexcept;
  bool isConnected() const noexcept;
  bool isAServer() const noexcept;
  bool server(uint16_t port = AUTO_PORT, int backlog = DEFAULT_BACKLOG) noexcept;
  bool accept(Socket &newClient) const noexcept;
  bool connect(const std::string &ipaddr, uint16_t port) noexcept;
  bool connect(uint32_t ip32, uint16_t port) noexcept;
  bool shutdown() noexcept;
  bool setBacklog(int backlog) noexcept;

private:
  bool createSocket() noexcept;
  std::string _ipaddr = "{uninitialized}";
  struct sockaddr_in _saddr;
  int _fd = -1;
  int _backlog;
  uint16_t _port;
  bool _isServer : 1;
  bool _isConnected : 1;
};

bool operator==(const Socket &sock, const int &fd);
bool operator==(const Socket &sock, const uint16_t &port);
} // namespace linet