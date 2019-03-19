#include "trace.hpp"
#include "Client.hpp"

namespace linet {
void Client::onConnect() noexcept
{
  if (_onConnect)
    _onConnect();
}

void Client::onDisconnect() noexcept
{
  if (_onDisconnect)
    _onDisconnect();
}

void Client::setOnConnect(const std::function<void()> &cb) noexcept
{
  _onConnect = cb;
}

void Client::setOnDisconnect(const std::function<void()> &cb) noexcept
{
  _onDisconnect = cb;
}

Client &Client::operator=(const Client &client)
{
  Socket::operator=(client);
  return *this;
}

bool operator==(const Client &sock, const int &fd)
{
  return sock.getFdHandle() == fd;
}

bool operator==(const Client &sock, const uint16_t &port)
{
  return sock.getPort() == port;
}
} // namespace linet