#include "folderWatcher.hpp"

FolderWatcher::FolderWatcher(uint64_t msDelay) noexcept
        : _msDelay(msDelay)
        , _isRunning(false)
{
  _internalLock.lock();
  _internalThread = std::thread(&FolderWatcher::internalJob, this);
  _internalThread.detach();
}

void FolderWatcher::deletionUpdate() noexcept
{
  auto it = _entries.begin();

  while (it != _entries.end()) {
    if (std::filesystem::exists(it->first.string()) == false) {
      it->first.deleted();
      it = _entries.erase(it);
    }
    else
      ++it;
  }
}

void FolderWatcher::outUpdate(std::vector<Folder>::iterator &file) noexcept
{
  auto it = _entries.find(*file);
  if (std::filesystem::exists(file->string()) == false && it != _entries.end()) {
    _entries.erase(it);
    return;
  }
  auto count = std::filesystem::last_write_time(file->string()).time_since_epoch().count();
  if (it != _entries.end() && it->second != count) {
    it->first.modified();
    it->second = count;
  }
}

void FolderWatcher::recursiveUpdate(std::vector<Folder>::iterator &itfolder) noexcept
{
  std::filesystem::recursive_directory_iterator folder(itfolder->string());

  for (auto &&f : folder) {
    if (!f.is_regular_file())
      continue;
    Folder entry(f.path().string());
    auto it = _entries.find(entry);
    auto count = std::filesystem::last_write_time(f).time_since_epoch().count();
    if (it == _entries.end()) {
      entry.inherite(*itfolder);
      entry.created();
      _entries[entry] = count;
    }
    else if (it->second != count) {
      entry.inherite(*itfolder);
      entry.modified();
      it->second = count;
    }
  }
}

void FolderWatcher::internalJob() noexcept
{
  _internalLock.lock();
  while (1) {
    auto start = std::chrono::steady_clock::now();
    toUntrack();
    toTrack();
    deletionUpdate();
    auto it = _trackedEntries.begin();
    while (it != _trackedEntries.end()) {
      if (std::filesystem::exists(it->string()) == false)
        continue;
      else if (std::filesystem::is_directory(it->string())) {
        recursiveUpdate(it);
      }
      else if (std::filesystem::is_regular_file(it->string())) {
        outUpdate(it);
      }
      ++it;
    }
    if (_isRunning == true)
      _internalLock.unlock();
    auto end = std::chrono::steady_clock::now();
    auto elapsed = end - start;
    if (elapsed < std::chrono::milliseconds(_msDelay))
      std::this_thread::sleep_for(std::chrono::milliseconds(_msDelay) - elapsed);
    _internalLock.lock();
  }
}

void FolderWatcher::toTrack() noexcept
{
  for (size_t i = 0; i < _toTrack.size(); ++i) {
    if (std::filesystem::is_regular_file(_toTrack[i].string())) {
      _entries[_toTrack[i]] =
              std::filesystem::last_write_time(_toTrack[i].string()).time_since_epoch().count();
      _toTrack[i].created();
    }
    _addLock.lock();
    _trackedEntries.push_back(_toTrack[i]);
    _addLock.unlock();
  }
  if (_toTrack.size() > 0) {
    _addLock.lock();
    _toTrack.clear();
    _addLock.unlock();
  }
}

void FolderWatcher::toUntrack() noexcept
{
  for (size_t i = 0; i < _toUntrack.size(); ++i) {
    _delLock.lock();
    auto it = std::find(_toTrack.begin(), _toTrack.end(), _toUntrack[i]);
    if (it != _toTrack.end()) {
      _toTrack.erase(it);
    }
    it = std::find(_trackedEntries.begin(), _trackedEntries.end(), _toUntrack[i]);
    if (it == _trackedEntries.end())
      continue;
    auto entry = _entries.begin();
    while (entry != _entries.end()) {
      if (entry->first.find(it->string(), 0) == 0) {
        _delLock.unlock();
        entry->first.deleted();
        _delLock.lock();
        entry = _entries.erase(entry);
      }
      else
        ++entry;
    }
    _trackedEntries.erase(it);
  }
  _toUntrack.clear();
  _delLock.unlock();
}

bool FolderWatcher::track(const std::string &folder,
                          const std::function<void(const std::string &)> &onCreate,
                          const std::function<void(const std::string &)> &onModify,
                          const std::function<void(const std::string &)> &onDelete) noexcept
{
  if (std::filesystem::is_directory(folder) == false
      && std::filesystem::is_regular_file(folder) == false)
    return false;
  _addLock.lock();
  if (_entries.find(folder) != _entries.end()
      || std::find(_trackedEntries.begin(), _trackedEntries.end(), folder) != _trackedEntries.end()
      || std::find(_toTrack.begin(), _toTrack.end(), folder) != _toTrack.end()) {
    _addLock.unlock();
    return false;
  }
  Folder f(folder);
  f.onCreate(onCreate);
  f.onModify(onModify);
  f.onDelete(onDelete);
  _toTrack.push_back(f);
  _addLock.unlock();
  return true;
}

bool FolderWatcher::untrack(const std::string &folder) noexcept
{
  _delLock.lock();
  if (std::find(_trackedEntries.begin(), _trackedEntries.end(), folder) == _trackedEntries.end()
      || std::find(_toUntrack.begin(), _toUntrack.end(), folder) != _toUntrack.end()) {
    _delLock.unlock();
    return false;
  }
  _toUntrack.push_back(folder);
  _delLock.unlock();
  return true;
}

const std::vector<Folder> &FolderWatcher::getTrackedEntries() const noexcept
{
  return _trackedEntries;
}

uint64_t FolderWatcher::delay() const noexcept
{
  return _msDelay;
}

void FolderWatcher::delay(uint64_t delay) noexcept
{
  _msDelay = delay;
}

void FolderWatcher::start() noexcept
{
  _internalLock.unlock();
  _isRunning = true;
}

void FolderWatcher::stop() noexcept
{
  _isRunning = false;
}

bool FolderWatcher::isRunning() const noexcept
{
  return _isRunning;
}
