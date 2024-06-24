#ifndef __POOLALLOCATOR_H__
#define __POOLALLOCATOR_H__

#include <queue>
#include <cstddef>
#include <string>
#include <filesystem>

#include "allocator.h"
#include "helpers/mappedFile.h"

namespace fs = std::filesystem;

class PoolAllocator;

namespace Metadata
{
    namespace PAllocator
    {
        void serialize(const fs::path &path, const std::string &name, PoolAllocator *allocator);
        void deserialize(const fs::path &path, const std::string &name, PoolAllocator *allocator);
    }
}

class PoolAllocator : public Allocator
{
public:
    PoolAllocator(MappedFile *mappedFile, long long blockSize = 4096ll);

    std::byte *allocate() override;

    void dellocate(std::byte *addr) override;

    void free() override;

    std::byte *getStart() override;

    friend void Metadata::PAllocator::serialize(const fs::path &, const std::string &, PoolAllocator *);
    friend void Metadata::PAllocator::deserialize(const fs::path &, const std::string &, PoolAllocator *);

private:
    long long blockSize_;
    MappedFile *mappedFile_;
    std::byte *start_;
    std::byte *current_;
    std::byte *end_;

    std::queue<std::byte *> freeBlocks_;

    PoolAllocator();
};
#endif // __POOLALLOCATOR_H__
