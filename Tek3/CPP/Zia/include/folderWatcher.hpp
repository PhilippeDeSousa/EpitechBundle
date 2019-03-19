#pragma once

#include <thread>
#include <mutex>
#include <unordered_map>
#include <filesystem>
#include <iostream>

#include "defaultConf.hpp"
#include "folder.hpp"

class FolderWatcher {
public:
  FolderWatcher(uint64_t msDelay = zia::DEFAULT_WATCHER_DELAY) noexcept;
  ~FolderWatcher() noexcept = default;
  bool track(const std::string &entryPath, const std::function<void(const std::string &)> &onCreate,
             const std::function<void(const std::string &)> &onModify,
             const std::function<void(const std::string &)> &onDelete) noexcept;
  bool untrack(const std::string &folder) noexcept;
  std::vector<std::filesystem::directory_entry> getFiles() const noexcept;
  const std::vector<Folder> &getTrackedEntries() const noexcept;
  uint64_t delay() const noexcept;
  void delay(uint64_t delay) noexcept;
  bool isRunning() const noexcept;
  void start() noexcept;
  void stop() noexcept;

private:
  void toTrack() noexcept;
  void toUntrack() noexcept;
  void internalJob() noexcept;
  void deletionUpdate() noexcept;
  void recursiveUpdate(std::vector<Folder>::iterator &itfolder) noexcept;
  void outUpdate(std::vector<Folder>::iterator &file) noexcept;
  std::unordered_map<Folder, int64_t, std::hash<std::string>> _entries;
  std::vector<Folder> _trackedEntries;
  std::mutex _internalLock;
  std::mutex _addLock;
  std::mutex _delLock;
  std::thread _internalThread;
  std::vector<Folder> _toTrack;
  std::vector<std::string> _toUntrack;
  uint64_t _msDelay;
  bool _isRunning : 1;
};
