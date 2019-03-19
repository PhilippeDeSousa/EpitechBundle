#include <algorithm>
#include <iostream>
#include <filesystem>
#include <vector>

#include "SharedModules.hpp"

namespace zia {

bool SharedModules::addModule(const std::string &path) noexcept
{
  if (isLoaded(path) == true)
    return false;
  zia::SharedObject obj;
  if (obj.openLib(path) == false) {
    return false;
  }
  obj.callFnc(getStageManager());
  _modules.push_back(std::move(obj));
  return true;
}

bool SharedModules::rmModule(const std::string &path) noexcept
{
  if (isLoaded(path) == false)
    return false;
  for (auto it = _modules.begin(); it != _modules.end(); ++it) {
    if (it->getPath() == path) {
      it->closeLib();
      auto &manager = getStageManager();
      manager.request().unhookAll(it->getName());
      it = _modules.erase(it);
      return true;
    }
  }
  return false;
}

bool SharedModules::isLoaded(const std::string &modulePath) const noexcept
{
  for (const auto &v : _modules) {
    if (v.getPath() == modulePath) {
      return true;
    }
  }
  return false;
}

void SharedModules::runModulesOnCtx(dems::Context &ctx) noexcept
{
  auto &manager = getStageManager();
  auto &map = manager.request().firstHooks();
  for (auto &&i : map)
    i.second.callback(ctx);
  map = manager.request().middleHooks();
  for (auto &&i : map)
    i.second.callback(ctx);
  map = manager.request().endHooks();
  for (auto &&i : map)
    i.second.callback(ctx);
}

void SharedModules::loadOneModule(const std::string &filePath) noexcept
{
  addModule(filePath);
}

void SharedModules::unloadModule(const std::string &filePath) noexcept
{
  rmModule(filePath);
}

const std::vector<SharedObject> &SharedModules::getModules() const noexcept
{
  return _modules;
}

void SharedModules::loadModules(const std::string &directoryPath) noexcept
{
  std::vector<std::string> files;

  if (!directoryPath.empty()) {
    for (const auto &entry : std::filesystem::directory_iterator(directoryPath))
      files.push_back(entry.path().string());
    std::sort(files.begin(), files.end());
    for (auto v : files) {
      if (addModule(v) == false)
        return;
    }
  }
}
} // namespace zia