#pragma once

#include <cstdio>
#include <mutex>

#include "colors.h"

int trace(const char string[], bool lock = true) noexcept;
int trace(bool isOk, bool lock = true) noexcept;
int trace(bool isOk, const char string[], bool lock = true) noexcept;
void traceLockMutex() noexcept;
void traceUnlockMutex() noexcept;

template <typename... Args> int trace(const char *format, Args... args) noexcept
{
  traceLockMutex();
  int f = fprintf(stderr, format, args...);
  traceUnlockMutex();
  return f;
}

template <typename... Args> int trace(bool isOk, const char *format, Args... args) noexcept
{
  int ret;

  traceLockMutex();
  ret = trace(isOk, false);
  ret += fprintf(stderr, format, args...);
  traceUnlockMutex();
  return ret;
}
