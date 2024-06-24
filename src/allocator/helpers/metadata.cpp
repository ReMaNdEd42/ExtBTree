#include "allocator/helpers/metadata.h"

json Metadata::deserialize(const fs::path &path, const std::string &name)
{
    std::fstream file;
    std::string md;
    json metadata;

    file.open(path / "metadata.json", std::ios::in);
    if (file.is_open())
    {
        file >> md;
        if (json::accept(md))
        {
            metadata = json::parse(md);
        }
        else
        {
            throw BtreeException("WRONG metadata:\njson is not valid");
        }
    }
    else
    {
        file.open(path / "metadata.json", std::ios::trunc | std::ios::in);
    }
    file.close();
    return metadata[name];
}

void Metadata::serialize(const fs::path &path, const std::string &name, const json &data)
{
    std::fstream file;
    std::string md;
    json metadata;

    file.open(path / "metadata.json", std::ios::in);
    if (file.is_open())
    {
        file >> md;
        if (json::accept(md))
        {
            metadata = json::parse(md);
        }
        else
        {
            throw BtreeException("WRONG metadata:\njson is not valid");
        }
    }
    else
    {
        file.open(path / "metadata.json", std::ios::trunc | std::ios::in);
    }
    file.close();

    metadata[name] = data;

    file.open(path / "metadata.json", std::ios::out);
    if (!file.is_open())
    {
        file.open(path / "metadata.json", std::ios::trunc | std::ios::out);
    }
    file << metadata;
    file.close();
}

void Metadata::PAllocator::serialize(const fs::path &path, const std::string &name, PoolAllocator *allocator)
{
    json metadata;
    metadata["blockSize"] = std::to_string(allocator->blockSize_);
    metadata["currentOffset"] = std::to_string(allocator->current_ - allocator->start_);
    metadata["endOffset"] = std::to_string(allocator->end_ - allocator->start_);
    while (!allocator->freeBlocks_.empty())
    {
        metadata["freeBlocksOffsets"].array().push_back((std::to_string(allocator->freeBlocks_.front() - allocator->start_)));
        allocator->freeBlocks_.pop();
    }
    Metadata::serialize(path, name, metadata);
}

void Metadata::PAllocator::deserialize(const fs::path &path, const std::string &name, PoolAllocator *allocator)
{
    json metadata = Metadata::deserialize(path, name);
    if (metadata.is_null())
    {
        return;
    }
    allocator->blockSize_ = atoll(metadata["blockSize"].get<std::string>().c_str());
    allocator->current_ = allocator->start_ + atoll(metadata["currentOffset"].get<std::string>().c_str());
    allocator->end_ = allocator->start_ + atoll(metadata["endOffset"].get<std::string>().c_str());
    for (auto &freeBlocksOffsets : metadata["freeBlocksOffsets"].array())
    {
        allocator->freeBlocks_.push(allocator->start_ + atoll(freeBlocksOffsets.get<std::string>().c_str()));
    }
}

void Metadata::MFile::serialize(const fs::path &path, const std::string &name, MappedFile *mappedFile)
{
    json metadata;
    metadata["size"] = std::to_string(mappedFile->size_);
    Metadata::serialize(path, name, metadata);
}

void Metadata::MFile::deserialize(const fs::path &path, const std::string &name, MappedFile *mappedFile)
{
    json metadata = Metadata::deserialize(path, name);
    if (metadata.is_null())
    {
        return;
    }
    mappedFile->resize(atoll(metadata["size"].get<std::string>().c_str()));
}
