#include "allocator/helpers/mappedFile.h"

MappedFile::MappedFile(const char *fileName, int flags, long long size)
{
  size_ = size;
  flags_ = flags;
  fd_ = open(fileName, O_RDWR | O_SYNC | O_DIRECT, S_IRWXU);
  if (fd_ < 0)
  {
    fd_ = open(fileName, O_RDWR | O_CREAT | O_SYNC | O_DIRECT, S_IRWXU);
    if (fd_ < 0)
      throw BtreeException("WRONG mmaping:\ncan`t create and open a file");
    ftruncate(fd_, size_);
  }
  addr_ = mmap(nullptr, size_, PROT_READ | PROT_WRITE, flags_, fd_, 0);
  if (addr_ == MAP_FAILED)
    throw BtreeException("WRONG mmaping:\ncan`t mmap a file");
  setMAdvise(MADV_NORMAL);
}

void MappedFile::resize(long long size)
{
  msync(addr_, size_, MS_SYNC);
  munmap(addr_, size_);
  ftruncate(fd_, size);
  posix_fadvise(fd_, 0, size_, advise_);
  addr_ = mmap(nullptr, size, PROT_READ | PROT_WRITE, flags_, fd_, 0);
  // addr_ = mremap(addr_, size_, size, MREMAP_MAYMOVE, );
  if (addr_ == MAP_FAILED)
    throw BtreeException("WRONG mremaping:\ncan`t mremap a file");
  size_ = size;
  // TODO: should we use munmap() with mmap() instead mremap()?
  madvise(addr_, size_, advise_);
}

MappedFile::~MappedFile()
{
  msync(addr_, size_, MS_SYNC);
  munmap(addr_, size_);
  close(fd_);
  // TODO: check return values, wich may be negative;
}

void *MappedFile::getAddr()
{
  return addr_;
}

long long MappedFile::getSize()
{
  return size_;
}

void MappedFile::setMAdvise(int advise)
{
  advise_ = advise;
  posix_fadvise(fd_, 0, size_, advise_);
  madvise(addr_, size_, advise_);
}