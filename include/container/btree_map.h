#ifndef __BTREE_MAP_H__
#define __BTREE_MAP_H__
#include <filesystem>
#include <memory>

#include "container/helpers/pair.h"

#include "btree/btree.h"
#include "btree/btree.cpp"

#include "btree/utils/btreeAlgorithm.h"

#include "allocator/poolAllocator.h"

#include "allocator/helpers/mappedFile.h"
#include "allocator/helpers/metadata.h"

template <typename K, typename V>
class btree_map
{
private:
    std::filesystem::path path_;
    std::unique_ptr<MappedFile> mf_;
    std::unique_ptr<PoolAllocator> pa_;
    std::unique_ptr<BTree<pair<K, V>>> btree_;

    btree_map();

public:
    btree_map(std::filesystem::path path);

    ~btree_map();

    void insert(pair<K, V> pair);

    std::optional<pair<K, V>> find(K key);

    void erase(K &key);

    void clear();

    int count();

    std::map<K, V> toMap();
};

#endif // __BTREE_MAP_H__