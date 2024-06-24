#ifndef __BTREE_SET_CPP__
#define __BTREE_SET_CPP__

#include "container/btree_set.h"
#include "btree/utils/btreeAlgorithm.h"

template <typename K>
btree_set<K>::btree_set(std::filesystem::path path) : path_{path}
{
    mf_ = std::make_unique<MappedFile>((path / "btree_temp").c_str(), MAP_SHARED | MAP_POPULATE);
    Metadata::MFile::deserialize(path, "mf", mf_.get());
    pa_ = std::make_unique<PoolAllocator>(mf_.get());
    Metadata::PAllocator::deserialize(path, "pa", pa_.get());
    try
    {
        long long rootOffset = atoll(Metadata::deserialize(path, "rootOffset").get<std::string>().c_str());
        btree_ = std::make_unique<BTree<K>>(pa_.get(), rootOffset);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        btree_ = std::make_unique<BTree<K>>(pa_.get());
    }
}
template <typename K>
btree_set<K>::~btree_set()
{
    Metadata::MFile::serialize(path_, "mf", mf_.get());
    Metadata::PAllocator::serialize(path_, "pa", pa_.get());
    Metadata::serialize(path_, "rootOffset", json(std::to_string(btree_->getRootOffset())));
}
template <typename K>
void btree_set<K>::insert(K key)
{
    btree_->insert(key);
}

template <typename K>
std::optional<K> btree_set<K>::find(K key)
{
    return btree_->search({key});
}

template <typename K>
void btree_set<K>::clear()
{
}

template <typename K>
std::set<K> btree_set<K>::toSet()
{
    return BtreeAlgorithm::toSet(btree_.get());
}

template <typename K>
int btree_set<K>::count()
{
    return 0;
}
#endif // __BTREE_SET_CPP__