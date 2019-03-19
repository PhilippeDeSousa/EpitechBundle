#include <cstring>

#ifdef __linux__
#  include <unistd.h>
#elif _WIN32
#  include <Winsock2.h>
#endif

#include "CBuffer.hpp"

CBuffer::CBuffer(size_t size) noexcept
        : _size(size)
{
  _buffer = std::make_unique<int8_t[]>(_size);
  clear();
}

size_t CBuffer::leftToRead(size_t toRead) const noexcept
{
  size_t left;

  if (_reader < _writer) {
    left = _writer - _reader;
    return (left > toRead) ? toRead : left;
  }
  left = _buffer.get() + _size - _reader;
  return (left > toRead) ? toRead : left;
}

size_t CBuffer::read(void *dest, size_t count) noexcept
{
  if (_writer == _reader && _isEmpty == true)
    return 0;
  size_t total = 0;
  while (total < count) {
    size_t rd = leftToRead(count - total);
    std::memcpy((int8_t *)dest + total, _reader, rd);
    _reader += rd;
    total += rd;
    if (_reader == _buffer.get() + _size)
      _reader = _buffer.get();
    if (_reader == _writer) {
      _isEmpty = true;
      return total;
    }
  }
  return total;
}

static ssize_t rdsize(size_t wr, size_t count, size_t maxlen)
{
  if (wr > maxlen)
    wr = maxlen;
  if (wr > count)
    wr = count;
  return (ssize_t)wr;
}

ssize_t CBuffer::fdread(int fd, size_t count) noexcept
{
  char block[4096];
  ssize_t total = 0;
  ssize_t rd;
  ssize_t wr;

  do {
    rd = rdsize(sizeLeft(), count, sizeof(block));
    rd = (ssize_t)read(block, rd);
#ifdef _WIN32
    wr = send(fd, block, rd, 0);
#else
    wr = ::write(fd, block, rd);
#endif
    if (wr == -1)
      return -1;
    total += wr;
  } while (rd == (ssize_t)sizeof(block) && rd == wr);
  return total;
}

ssize_t CBuffer::fdread(int fd) noexcept
{
  char block[4096];
  ssize_t total = 0;
  ssize_t rd;
  ssize_t wr;

  do {
    rd = (ssize_t)read(block);
#ifdef _WIN32
    wr = send(fd, block, rd, 0);
#else
    wr = ::write(fd, block, rd);
#endif
    if (wr == -1)
      return -1;
    total += wr;
  } while (rd == (ssize_t)sizeof(block) && rd == wr);
  return total;
}

size_t CBuffer::leftToWrite(size_t toWrite) const noexcept
{
  size_t left;

  if (_writer < _reader)
    left = _reader - _writer;
  else
    left = _buffer.get() + _size - _writer;
  return (left > toWrite) ? toWrite : left;
}

size_t CBuffer::write(const void *src, size_t count) noexcept
{
  if (_writer == _reader && _isEmpty == false)
    return 0;
  if (count)
    _isEmpty = false;
  size_t written = 0;
  while (written < count) {
    size_t wr = leftToWrite(count - written);
    std::memcpy(_writer, (const int8_t *)src + written, wr);
    _writer += wr;
    written += wr;
    if (_writer == _buffer.get() + _size)
      _writer = _buffer.get();
    if (_writer == _reader)
      return written;
  }
  return written;
}

ssize_t CBuffer::fdwrite(int fd, size_t count) noexcept
{
  char block[4096];
  ssize_t total = 0;
  ssize_t rd;
  ssize_t wr;

  do {
    rd = rdsize(sizeLeft(), count, sizeof(block));
#ifdef _WIN32
    rd = recv(fd, block, sizeof(block), 0);
#else
    rd = ::read(fd, block, sizeof(block));
#endif
    if (rd == -1)
      return -1;
    wr = (ssize_t)write(block, rd);
    total += wr;
  } while (rd == (ssize_t)sizeof(block) && rd == wr);
  return total;
}

ssize_t CBuffer::fdwrite(int fd) noexcept
{
  char block[4096];
  ssize_t total = 0;
  ssize_t rd;
  ssize_t wr;

  do {
#ifdef _WIN32
    rd = recv(fd, block, sizeof(block), 0);
#else
    rd = ::read(fd, block, sizeof(block));
#endif
    if (rd == -1)
      return -1;
    wr = (ssize_t)write(block, rd);
    total += wr;
  } while (rd == (ssize_t)sizeof(block) && rd == wr);
  return total;
}

size_t CBuffer::sizeLeft() const noexcept
{
  if (_reader < _writer)
    return (size_t)((int8_t *)_size - _writer + _reader);
  else if (_reader > _writer)
    return _reader - _writer;
  return (_isEmpty) ? _size : 0;
}

size_t CBuffer::size() const noexcept
{
  return _size - sizeLeft();
}

void CBuffer::clear() noexcept
{
  _reader = _buffer.get();
  _writer = _buffer.get();
  _isEmpty = true;
}