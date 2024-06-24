#ifndef __METADATA_H__
#define __METADATA_H__
#include <fstream>
#include <filesystem>

#include "json/json.hpp"
#include "btree/btreeException.h"
#include "allocator/poolAllocator.h"
#include "allocator/helpers/mappedFile.h"

using json = nlohmann::json;
namespace fs = std::filesystem;

namespace Metadata
{
    void serialize(const fs::path &path, const std::string &name, const json &data);
    json deserialize(const fs::path &path, const std::string &name);

    namespace PAllocator
    {
        void serialize(const fs::path &path, const std::string &name, PoolAllocator *allocator);
        void deserialize(const fs::path &path, const std::string &name, PoolAllocator *allocator);
    };
    namespace MFile
    {
        void serialize(const fs::path &path, const std::string &name, MappedFile *mappedFile);
        void deserialize(const fs::path &path, const std::string &name, MappedFile *mappedFile);
    };
};
#endif
