#include <cstring>

#include <iostream>

#include "zia.hpp"
#include "SharedModules.hpp"
#include "Stage.hpp"

static void help(const char *bin)
{
#ifdef _WIN32
  const char *last = ::strrchr(bin, '\\');
#else
  const char *last = ::strrchr(bin, '/');
#endif
  if (last++ == nullptr)
    last = bin;
  std::cerr << "Usage:\t" << last << " [CONFIG FILE]" << std::endl;
  std::cerr << "      \t" << last << " --help" << std::endl;
}

int main(int ac, char **av)
{
  if (ac > 2 || (ac == 2 && ::strcmp(av[1], "--help") == 0)) {
    help(av[0]);
    return (0);
  }
  zia::Server server;
  if (ac == 2)
    server.configFilePath(av[1]);
  server.run();
  return (0);
}
