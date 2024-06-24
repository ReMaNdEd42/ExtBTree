#ifndef __MAPPED_FILE_H__
#define __MAPPED_FILE_H__
#include <sys/fcntl.h>
#include <unistd.h>
#include <string>
#include <sys/mman.h>
#include <filesystem>

#include "btree/btreeException.h"


namespace fs = std::filesystem;

class MappedFile;

namespace Metadata
{
  namespace MFile
  {
    void serialize(const fs::path &path, const std::string &name, MappedFile *mappedFile);
    void deserialize(const fs::path &path, const std::string &name, MappedFile *appedFile);
  }
}

class MappedFile
{
private:
  int fd_;

  int flags_;

  void *addr_;

  long long size_;

  int advise_;

public:
  MappedFile(const char *fileName, int flags = MAP_SHARED, long long size = 4096ll);

  MappedFile() {}

  ~MappedFile();

  void *getAddr();

  long long getSize();

  void resize(long long size);

  void setMAdvise(int advise);

  friend void Metadata::MFile::serialize(const fs::path &, const std::string &, MappedFile *);
  friend void Metadata::MFile::deserialize(const fs::path &, const std::string &, MappedFile *);
};
#endif
// TODO: rewrite it using boos.ipc includin inner mapped_file realisation