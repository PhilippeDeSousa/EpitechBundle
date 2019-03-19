#pragma once

#include <functional>

#include "CBuffer.hpp"
#include "Socket.hpp"

namespace linet {
class Client : public Socket, public CBuffer {
public:
  Client() = default;
  Client &operator=(const Client &client);
  void onConnect() noexcept;
  void onDisconnect() noexcept;
  void setOnConnect(const std::function<void()> &callback) noexcept;
  void setOnDisconnect(const std::function<void()> &callback) noexcept;

private:
  std::function<void()> _onConnect;
  std::function<void()> _onDisconnect;
};

bool operator==(const Client &sock, const int &fd);
bool operator==(const Client &sock, const uint16_t &port);
} // namespace linet