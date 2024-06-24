#include "allocator/poolAllocator.h"

PoolAllocator::PoolAllocator(MappedFile *mappedFile, long long blockSize) : blockSize_{blockSize}, mappedFile_{mappedFile}
{
    start_ = (std::byte *)mappedFile_->getAddr();
    current_ = start_;
    end_ = start_ + mappedFile_->getSize();
}

std::byte *PoolAllocator::allocate()
{

    std::byte *addr;

    if (!freeBlocks_.empty())
    {
        addr = freeBlocks_.front();
        freeBlocks_.pop();
    }
    else if (end_ - current_ <= blockSize_)
    {
        mappedFile_->resize(mappedFile_->getSize() + blockSize_ * 1024ll);

        long long currentOffset = current_ - start_;

        start_ = (std::byte *)mappedFile_->getAddr();
        current_ = start_ + currentOffset;
        addr = current_;
        current_ = current_ + blockSize_;
        end_ = start_ + mappedFile_->getSize();
    }
    else
    {
        addr = current_;
        current_ = current_ + blockSize_;
    }
    return addr;
}

void PoolAllocator::dellocate(std::byte *addr)
{
    bool isInTheRange = addr - start_ >= 0 &&
                        end_ - addr > 0;

    bool isNoEndOfTheBlock = (end_ - addr) / blockSize_ > 0;

    if (isInTheRange)
    {
        if (isNoEndOfTheBlock)
        {
            freeBlocks_.push(addr);
        }
        else
        {
            throw BtreeException("WRONG dellocation:\ncan`t dellocate end of the allocated block");
        }
    }
    else
    {
        throw BtreeException("WRONG dellocation:\ncan`t dellocate out of allocated range");
    }
}

void PoolAllocator::free()
{
    current_ = start_;
    while (!freeBlocks_.empty())
    {
        freeBlocks_.pop();
    }
}

std::byte *PoolAllocator::getStart()
{
    return start_;
}