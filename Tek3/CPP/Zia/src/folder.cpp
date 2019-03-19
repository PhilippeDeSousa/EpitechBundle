#include "folder.hpp"

#ifdef __linux__
static void dummy(__attribute__((unused)) const std::string &path)
{
}
#elif _WIN32
static void dummy(const std::string &path)
{
  (void)path;
}
#endif

Folder::Folder(const std::string &str)
        : std::string(str)
{
  _onCreate = &dummy;
  _onModify = &dummy;
  _onDelete = &dummy;
}

Folder::Folder(Folder &&f)
{
  string() = std::move(f.string());
  inherite(f);
}

Folder::Folder(const Folder &f)
        : std::string(f)
{
  inherite(f);
}

Folder Folder::operator=(const Folder &other)
{
  Folder f(other);
  return f;
}

void Folder::onCreate(const std::function<void(const std::string &)> &cb) noexcept
{
  _onCreate = cb;
}

void Folder::onModify(const std::function<void(const std::string &)> &cb) noexcept
{
  _onModify = cb;
}

void Folder::onDelete(const std::function<void(const std::string &)> &cb) noexcept
{
  _onDelete = cb;
}

void Folder::created() const noexcept
{
  _onCreate(*this);
}

void Folder::modified() const noexcept
{
  _onModify(*this);
}

void Folder::deleted() const noexcept
{
  _onDelete(*this);
}

void Folder::inherite(const Folder &f) noexcept
{
  _onCreate = f._onCreate;
  _onModify = f._onModify;
  _onDelete = f._onDelete;
}