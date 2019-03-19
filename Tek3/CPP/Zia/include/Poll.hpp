#pragma once

#ifdef __linux__
#  include <poll.h>
#elif _WIN32
#  include <Winsock2.h>
#endif

#include <vector>

class Poll {
public:
  bool addFd(int fd, short event = POLLIN) noexcept;
  bool delFd(int fd) noexcept;
  bool changeFd(int fd, short event = 0) noexcept;
  bool run(int timeout = -1) noexcept;
  const std::vector<int> &getEvents();

private:
  std::vector<struct pollfd> _fds;
  std::vector<int> _triggered;
};