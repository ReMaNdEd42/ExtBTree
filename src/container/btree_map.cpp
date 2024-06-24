#ifndef __BTREE_MAP_CPP__
#define __BTREE_MAP_CPP__

#include "container/btree_map.h"

template <typename K, typename V>
btree_map<K, V>::btree_map(std::filesystem::path path) : path_{path}
{
    mf_ = std::make_unique<MappedFile>((path / "btree_temp").c_str(), MAP_SHARED | MAP_POPULATE);
    Metadata::MFile::deserialize(path, "mf", mf_.get());
    pa_ = std::make_unique<PoolAllocator>(mf_.get());
    Metadata::PAllocator::deserialize(path, "pa", pa_.get());
    try
    {
        long long rootOffset = atoll(Metadata::deserialize(path, "rootOffset").get<std::string>().c_str());
        btree_ = std::make_unique<BTree<pair<K, V>>>(pa_.get(), rootOffset);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        btree_ = std::make_unique<BTree<pair<K, V>>>(pa_.get());
    }
}
template <typename K, typename V>
btree_map<K, V>::~btree_map()
{
    Metadata::MFile::serialize(path_, "mf", mf_.get());
    Metadata::PAllocator::serialize(path_, "pa", pa_.get());
    Metadata::serialize(path_, "rootOffset", json(std::to_string(btree_->getRootOffset())));
}
template <typename K, typename V>
void btree_map<K, V>::insert(pair<K, V> pair)
{
    btree_->insert(pair);
}

template <typename K, typename V>
std::optional<pair<K, V>> btree_map<K, V>::find(K key)
{
    return btree_->search({key});
}

template <typename K, typename V>
void btree_map<K, V>::clear()
{
}

template <typename K, typename V>
int btree_map<K, V>::count()
{
    return 0;
}

template <typename K, typename V>
std::map<K, V> btree_map<K, V>::toMap()
{
    return BtreeAlgorithm::toMap(btree_.get());
}
#endif //__BTREE_MAP_CPP__