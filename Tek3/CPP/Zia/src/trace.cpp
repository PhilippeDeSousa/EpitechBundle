#include "trace.hpp"

static std::mutex traceMutex;

void traceLockMutex() noexcept
{
  traceMutex.lock();
}

void traceUnlockMutex() noexcept
{
  traceMutex.unlock();
}

int trace(const char string[], bool lock) noexcept
{
  if (lock)
    traceLockMutex();
  int f = fputs(string, stderr);
  if (lock)
    traceUnlockMutex();
  return f;
}

int trace(bool isOk, bool lock) noexcept
{
  const char *color;

  if (isOk == true)
    color = "[ " BOLDGREEN "OK" RESET " ] ";
  else
    color = "[ " BOLDRED "KO" RESET " ] ";
  if (lock)
    traceLockMutex();
  int f = fputs(color, stderr);
  if (lock)
    traceUnlockMutex();
  return f;
}

int trace(bool isOk, const char string[], bool lock) noexcept
{
  int ret = trace(isOk, lock);
  return ret + trace(string, lock);
}