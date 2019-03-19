#pragma once

#include <cstdint>
#include <memory>

#ifdef _WIN32
typedef long int ssize_t;
#endif

class CBuffer {
public:
  CBuffer(size_t size = 1 << 16) noexcept;
  size_t read(void *dest, size_t count) noexcept;
  ssize_t fdread(int destFd, size_t count) noexcept;
  ssize_t fdread(int destFd) noexcept;
  template <typename T> size_t read(T &dest, size_t count)
  {
    return read(&dest, count);
  }
  template <typename T> size_t read(T &dest)
  {
    return read(&dest, sizeof(dest));
  }
  size_t write(const void *src, size_t count) noexcept;
  ssize_t fdwrite(int srcFd, size_t count) noexcept;
  ssize_t fdwrite(int srcFd) noexcept;
  template <typename T> size_t write(T &src, size_t count)
  {
    return write(&src, count);
  }
  template <typename T> size_t write(T &src)
  {
    return write(&src, sizeof(src));
  }
  size_t sizeLeft() const noexcept;
  size_t size() const noexcept;
  void clear() noexcept;
  template <typename T> size_t retrieve(T &dest) noexcept
  {
    dest.reserve(size());
    int8_t byte;
    size_t total = size();
    while (_isEmpty == false) {
      read(byte);
      dest.push_back(byte);
    }
    return total;
  }

private:
  size_t leftToRead(size_t toRead) const noexcept;
  size_t leftToWrite(size_t toWrite) const noexcept;
  size_t _size;
  int8_t *_reader;
  int8_t *_writer;
  std::unique_ptr<int8_t[]> _buffer;
  bool _isEmpty : 1;
};