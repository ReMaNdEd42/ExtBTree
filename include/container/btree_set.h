#ifndef __BTREE_SET_H__
#define __BTREE_SET_H__
#include <filesystem>
#include <memory>
#include <set>

#include "btree/btree.h"
#include "btree/btree.cpp"
#include "btree/utils/btreeAlgorithm.h"

#include "allocator/poolAllocator.h"

#include "allocator/helpers/mappedFile.h"
#include "allocator/helpers/metadata.h"

template <typename K>
class btree_set
{
private:
    std::filesystem::path path_;
    std::unique_ptr<MappedFile> mf_;
    std::unique_ptr<PoolAllocator> pa_;
    std::unique_ptr<BTree<K>> btree_;

    btree_set();

public:
    btree_set(std::filesystem::path path);

    ~btree_set();

    void insert(K key);

    std::optional<K> find(K key);

    std::set<K> toSet();

    void erase(K key);

    void clear();

    int count();
};

#endif // __BTREE_SET_H__