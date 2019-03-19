#include <algorithm>

#include "trace.hpp"
#include "Poll.hpp"

static bool operator==(const struct pollfd &a, const int &fd)
{
  return a.fd == fd;
}

bool Poll::addFd(int fd, short event) noexcept
{
  auto it = std::find(_fds.begin(), _fds.end(), fd);
  if (it == _fds.end()) {
    struct pollfd pfd = {
#ifdef __linux__
            fd,
#elif _WIN32
            (SOCKET)fd,
#endif
            event,
            0,
    };
    _fds.push_back(pfd);
    return true;
  }
  return false;
}

bool Poll::delFd(int fd) noexcept
{
  auto it = std::find(_fds.begin(), _fds.end(), fd);

  if (it == _fds.end())
    return false;
  _fds.erase(it);
  return true;
}

bool Poll::changeFd(int fd, short event) noexcept
{
  auto it = std::find(_fds.begin(), _fds.end(), fd);

  if (it == _fds.end())
    return false;
  it->events = event;
  return true;
}

bool Poll::run(int timeout) noexcept
{
  if (_fds.size() == 0)
    return false;
#ifdef __linux__
  int p = poll(_fds.data(), _fds.size(), timeout);
#elif _WIN32
  int p = WSAPoll(_fds.data(), _fds.size(), timeout);
#endif
  if (p <= 0)
    return false;
  _triggered.clear();
  _triggered.reserve(p);
  for (auto &i : _fds)
    if (i.revents)
      _triggered.push_back(i.fd);
  return true;
}

const std::vector<int> &Poll::getEvents()
{
  return _triggered;
}
