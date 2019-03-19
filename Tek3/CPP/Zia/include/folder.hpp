#pragma once

#include <string>
#include <functional>

class Folder : public std::string {
public:
  Folder(const std::string &str);
  ~Folder() = default;
  Folder(Folder &&f);
  Folder(const Folder &f);
  Folder operator=(const Folder &other);
  void onCreate(const std::function<void(const std::string &)> &cb) noexcept;
  void onModify(const std::function<void(const std::string &)> &cb) noexcept;
  void onDelete(const std::function<void(const std::string &)> &cb) noexcept;
  void inherite(const Folder &f) noexcept;
  void created() const noexcept;
  void modified() const noexcept;
  void deleted() const noexcept;
  std::string &string() noexcept
  {
    return *this;
  };
  const std::string &string() const noexcept
  {
    return *this;
  };

private:
  std::function<void(const std::string &)> _onCreate;
  std::function<void(const std::string &)> _onModify;
  std::function<void(const std::string &)> _onDelete;
};
