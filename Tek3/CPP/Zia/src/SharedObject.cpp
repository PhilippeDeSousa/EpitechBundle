#ifdef __linux__
#  include <dlfcn.h>
#elif _WIN32
#  include <Windows.h>
#endif
#include "SharedObject.hpp"
#include "Stage.hpp"

namespace zia {
void SharedObject::closeLib() noexcept
{
  if (_handler != nullptr) {
#ifdef _WIN32
    FreeLibrary(_handler);
#else
    dlclose(_handler);
#endif
  }
  _handler = nullptr;
}

bool SharedObject::openLib(const std::string &path) noexcept
{
#ifdef __linux
  void *_handler = dlopen(path.c_str(), RTLD_LAZY);
#elif _WIN32
  HMODULE _handler = LoadLibraryA(path.c_str());
#endif
  if (_handler == nullptr)
    return false;
  setPath(path);
#ifdef __linux__
  _fnc = (registerHooks_t)dlsym(_handler, "registerHooks");
#elif _WIN32
  _fnc = (registerHooks_t)GetProcAddress(_handler, "registerHooks");
#endif
  if (_fnc == NULL)
    return false;
  return true;
}

const std::string &SharedObject::getName() const noexcept
{
  return _name;
}

const std::string &SharedObject::getPath() const noexcept
{
  return _path;
}

void SharedObject::setPath(const std::string &path) noexcept
{
  _path = path;
}

void SharedObject::callFnc(dems::StageManager &manager) noexcept
{
  _name = _fnc(manager);
}
}