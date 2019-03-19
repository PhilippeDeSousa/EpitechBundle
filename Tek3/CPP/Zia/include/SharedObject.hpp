
#pragma once

#include <iostream>
#include "Stage.hpp"

#ifdef _WIN32
#  include <Windows.h>
#endif

typedef std::string (*registerHooks_t)(dems::StageManager &manager);

namespace zia {
class SharedObject {
public:
  SharedObject() = default;
  ~SharedObject() = default;
  bool openLib(const std::string &path) noexcept;
  void closeLib() noexcept;
  void callFnc(dems::StageManager &manager) noexcept;
  const std::string &getPath() const noexcept;
  const std::string &getName() const noexcept;
  void setPath(const std::string &path) noexcept;
private:
#ifdef _WIN32
  HMODULE _handler = NULL;
#else
  void *_handler = NULL;
#endif
  registerHooks_t _fnc;
  std::string _path;
  std::string _name;
};
} // namespace zia
