#ifndef __BTREE_ALGORITHM_H__
#define __BTREE_ALGORITHM_H__
#include <set>
#include <map>
#include <iostream>
#include "btree/btree.h"
#include "container/helpers/pair.h"
class BtreeAlgorithm
{
public:
    template <typename K, int pageSize, int t>
    static void toSet(std::set<K> &set, Node<K, t> *node, BTree<K, pageSize> *btree)
    {
        for (size_t i = 0; i < node->size; i++)
        {
            set.insert(node->keys[i]);
        }
        if (node->leaf)
        {
            return;
        }
        for (size_t i = 0; i < node->size + 1; i++)
        {
            toSet(set, btree->read(node->children[i]), btree);
        }
    }
    template <typename K, typename V, int pageSize, int t>
    static void toMap(std::map<K, V> &map, Node<pair<K, V>, t> *node, BTree<pair<K, V>, pageSize> *btree)
    {
        for (size_t i = 0; i < node->size; i++)
        {
            pair<K, V> key = node->keys[i];
            map.insert(std::make_pair(key.first, key.second));
        }
        if (node->leaf)
        {
            return;
        }
        for (size_t i = 0; i < node->size + 1; i++)
        {
            toMap(map, btree->read(node->children[i]), btree);
        }
    }

    template <typename K, int pageSize>
    static std::set<K> toSet(BTree<K, pageSize> *btree)
    {
        auto node = btree->read(btree->rootOffset_);
        std::set<K> set;
        toSet(set, node, btree);
        return set;
    }

    template <typename K, typename V, int pageSize>
    static std::map<K, V> toMap(BTree<pair<K, V>, pageSize> *btree)
    {
        auto node = btree->read(btree->rootOffset_);
        std::map<K, V> map;
        toMap(map, node, btree);
        return map;
    }
};

#endif // __BTREE_ALGORITHM_H__
