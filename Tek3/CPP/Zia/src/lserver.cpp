#include <cstring>

#include <algorithm>
#include <iostream>

#include "trace.hpp"
#include "zia.hpp"
#include "lserver.hpp"

#include "SharedModules.hpp"

namespace linet {
bool ServerTCP::update(int timeout, zia::Server &server) noexcept
{
  if (_poll.run(timeout) == false)
    return false;
  auto &evts = _poll.getEvents();
  for (auto &fd : evts) {
    auto it = _clients.find(fd);
    if (it != _clients.end()) {
      ssize_t wr = it->second.fdwrite(fd);
      if (wr <= 0)
        eject(fd);
      else {
        dems::Context ctx;
        ctx.socketFd = it->second.getFdHandle();
        ctx.rawData.resize(it->second.size());
        it->second.read(ctx.rawData.data(), ctx.rawData.size());
        server.runContext(ctx);
        it->second.clear();
        it->second.write(ctx.rawData.data(), ctx.rawData.size());
        it->second.fdread(fd);
        eject(fd);
      }
    }
    else {
      auto listener = std::find(_listeners.begin(), _listeners.end(), fd);
      if (listener == _listeners.end())
        continue;
      Client newClient;
      bool status = listener->accept(newClient);
      if (status == true) {
        newClient.onConnect();
        status = _poll.addFd(newClient.getFdHandle());
        if (status == true)
          _clients[newClient.getFdHandle()] = newClient;
      }
      trace(status, "%s: connected\n", newClient.getIpv4().c_str());
    }
  }
  return true;
}

bool ServerTCP::eject(int fd) noexcept
{
  auto it = _clients.find(fd);

  bool status = _poll.delFd(fd);
  trace(status, "%s: disconnected\n", it->second.getIpv4().c_str());
  it->second.onDisconnect();
  it->second.shutdown();
  _clients.erase(it);
  return status;
}

bool ServerTCP::addListener(uint16_t port, int backlog) noexcept
{
  auto it = std::find(_listeners.begin(), _listeners.end(), port);

  if (it == _listeners.end()) {
    auto &i = _listeners.emplace_back(port, backlog);
    if (i.isAServer() == false || _poll.addFd(i.getFdHandle()) == false) {
      _listeners.pop_back();
      return false;
    }
    return true;
  }
  return false;
}

bool ServerTCP::addListener(uint16_t port) noexcept
{
  return addListener(port, linet::DEFAULT_BACKLOG);
}

bool ServerTCP::delListener(uint16_t port) noexcept
{
  auto it = std::find(_listeners.begin(), _listeners.end(), port);

  if (it == _listeners.end())
    return false;
  bool status = _poll.delFd(it->getFdHandle());
  _listeners.erase(it);
  return status;
}

bool ServerTCP::setBacklog(uint16_t port, int newBacklog) noexcept
{
  auto it = std::find(_listeners.begin(), _listeners.end(), port);

  if (it == _listeners.end())
    return false;
  return it->setBacklog(newBacklog);
}

bool ServerTCP::setBacklog(int newBacklog) noexcept
{
  bool ret = true;

  for (auto &&i : _listeners) {
    bool status = i.setBacklog(newBacklog);
    trace(status, "Listener{%u}: setBacklog{%d}\n", i.getPort(), newBacklog);
    if (status == false)
      ret = false;
  }
  return ret;
}

const std::unordered_map<int, Client> &ServerTCP::getClients() const noexcept
{
  return _clients;
}

std::vector<uint16_t> ServerTCP::getRunningPorts() const noexcept
{
  std::vector<uint16_t> v;

  v.reserve(_listeners.size());
  for (auto &&i : _listeners)
    v.push_back(i.getPort());
  return v;
}

uint16_t ServerTCP::getLastPort() const noexcept
{
  return _listeners.back().getPort();
}

} // namespace linet
