
#pragma once

#include <iostream>
#include <vector>

#include "SharedObject.hpp"
#include "Stage.hpp"
#include "AModulesManager.hpp"

namespace zia {
class SharedModules : public dems::AModulesManager {
public:
  SharedModules() noexcept {};
  virtual ~SharedModules() noexcept = default;
  bool addModule(const std::string &path) noexcept;
  bool rmModule(const std::string &path) noexcept;
  void loadModules(const std::string &directoryPath) noexcept;
  void loadOneModule(const std::string &filePath) noexcept;
  void unloadModule(const std::string &filePath) noexcept;
  void operator()()
  {
    for (auto it : _modules)
      it.callFnc(getStageManager());
  }
  const std::vector<SharedObject> &getModules() const noexcept;
  void runModulesOnCtx(dems::Context &ctx) noexcept;
  bool isLoaded(const std::string &modulePath) const noexcept;

private:
  std::vector<SharedObject> _modules;
};
} // namespace zia
