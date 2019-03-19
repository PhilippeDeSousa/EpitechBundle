#ifdef __linux__
#  include <unistd.h>
#  include <netdb.h>
#elif _WIN32
#  define _WINSOCK_DEPRECATED_NO_WARNINGS 1
#  include <winsock2.h>
#  include <winsock.h>
#  include <windows.h>
#  include <ws2tcpip.h>
#  define SHUT_RDWR SD_BOTH
#endif

#include "trace.hpp"
#include "Socket.hpp"


namespace linet {
#ifdef _WIN32
static void winCleanup()
{
  WSACleanup();
}

Socket::Socket() noexcept
        : _isServer(false)
        , _isConnected(false)
{
  static bool done = false;

  if (done == false) {
    WSADATA WSAData;
    WSAStartup(MAKEWORD(2, 0), &WSAData);
    atexit(&winCleanup);
    done = !done;
  }
}
#endif

Socket::Socket(uint16_t port, int backlog) noexcept
#ifdef _WIN32
        : Socket::Socket()
#else
        : _isServer(false)
        , _isConnected(false)
#endif
{
  server(port, backlog);
}

uint16_t Socket::getPort() const noexcept
{
  return _port;
}

int Socket::getBacklog() const noexcept
{
  return _backlog;
}

int Socket::getFdHandle() const noexcept
{
  return _fd;
}

const std::string &Socket::getIpv4() const noexcept
{
  return _ipaddr;
}

bool Socket::isConnected() const noexcept
{
  return _isConnected;
}

bool Socket::isAServer() const noexcept
{
  return _isServer;
}

bool Socket::createSocket() noexcept
{
  _fd = socket(AF_INET, SOCK_STREAM, 0);
  return (_fd == -1) ? false : true;
}

bool Socket::server(uint16_t port, int backlog) noexcept
{
  struct sockaddr *p = (struct sockaddr *)&_saddr;
  socklen_t len = sizeof(*p);

  if (createSocket() == false)
    return false;
  _backlog = backlog;
  _saddr.sin_addr.s_addr = INADDR_ANY;
  _saddr.sin_family = AF_INET;
  _saddr.sin_port = htons(port);
  if (bind(_fd, p, sizeof(_saddr)) == -1)
    return false;
  if ((port == 0 && getsockname(_fd, p, &len) == -1) || listen(_fd, backlog) == -1)
    return false;
  _port = ntohs(_saddr.sin_port);
  _isServer = true;
  _ipaddr = "{localhost}";
  return true;
}

Socket &Socket::operator=(const Socket &other)
{
  _ipaddr = std::move(other._ipaddr);
  _saddr = std::move(other._saddr);
  _fd = std::move(other._fd);
  _backlog = std::move(other._backlog);
  _port = std::move(other._port);
  _isServer = other._isServer;
  _isConnected = other._isConnected;
  return *this;
}

bool Socket::accept(Socket &newClient) const noexcept
{
  socklen_t len = sizeof(newClient._saddr);

  if (_isServer == false)
    return false;
  newClient._fd = ::accept(_fd, (struct sockaddr *)&newClient._saddr, &len);
  if (newClient._fd == -1)
    return false;
  newClient._isConnected = true;
  newClient._port = _port;
  newClient._ipaddr = inet_ntoa(newClient._saddr.sin_addr);
  return true;
}

bool Socket::connect(const std::string &ipaddr, uint16_t port) noexcept
{
  uint32_t ip_addr;
  struct hostent *info;

  info = gethostbyname(ipaddr.c_str());
  if (info == NULL)
    return false;
  ip_addr = ((struct in_addr *)info->h_addr)->s_addr;
  return (connect(ip_addr, port));
}

bool Socket::connect(uint32_t ip32, uint16_t port) noexcept
{
  if (createSocket() == false)
    return false;
  _saddr.sin_addr.s_addr = ip32;
  _saddr.sin_port = htons(port);
  _saddr.sin_family = AF_INET;
  if (::connect(_fd, (struct sockaddr *)&_saddr, sizeof(_saddr)) == -1)
    return false;
  _isConnected = true;
  _port = ntohs(_saddr.sin_port);
  _ipaddr = inet_ntoa(_saddr.sin_addr);
  return true;
}

bool Socket::shutdown() noexcept
{
  if (_fd != -1 && ::shutdown(_fd, SHUT_RDWR) == -1)
    return false;
  _fd = -1;
  _isConnected = false;
  _ipaddr = "{shutdowned}";
  return true;
}

bool Socket::setBacklog(int backlog) noexcept
{
  if (_isServer == false || ::listen(_fd, backlog) == -1)
    return false;
  return true;
}

bool operator==(const Socket &sock, const int &fd)
{
  return sock.getFdHandle() == fd;
}

bool operator==(const Socket &sock, const uint16_t &port)
{
  return sock.getPort() == port;
}
} // namespace linet
