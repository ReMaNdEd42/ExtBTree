#include "btree/btree.h"
#ifndef __BTREE_CPP_
#define __BTREE_CPP_
template <typename K, int pageSize>
BTree<K, pageSize>::BTree(Allocator *allocator, long long rootOffset)
{
    allocator_ = allocator;
    rootOffset_ = rootOffset;
}

template <typename K, int pageSize>
BTree<K, pageSize>::BTree(Allocator *allocator)
{
    allocator_ = allocator;
    create();
}

template <typename K, int pageSize>
Node<K, BTree<K, pageSize>::t> *BTree<K, pageSize>::read(long long offset)
{
    return new (allocator_->getStart() + offset) Node<K, t>;
}

template <typename K, int pageSize>
long long BTree<K, pageSize>::allocate()
{
    return allocator_->allocate() - allocator_->getStart();
}

template <typename K, int pageSize>
void BTree<K, pageSize>::dellocate(long long nodeOffset)
{
    allocator_->dellocate(allocator_->getStart() + nodeOffset);
}

template <typename K, int pageSize>
void BTree<K, pageSize>::create()
{
    auto nodeOffset = allocate();
    auto node = read(nodeOffset);
    node->leaf = true;
    node->size = 0;
    this->rootOffset_ = nodeOffset;
}

template <typename K, int pageSize>
void BTree<K, pageSize>::splitChild(long long parentOffset, int i)
{
    auto newChildOffset = allocate();
    auto newChild = read(newChildOffset);

    auto parent = read(parentOffset);
    auto child = read(parent->children[i]);

    newChild->leaf = child->leaf;
    newChild->size = t - 1;
    for (int j = 0; j < newChild->size; j++)
    {
        newChild->keys[j] = child->keys[j + t];
    }
    if (!child->leaf)
    {
        for (int j = 0; j < t; j++)
        {
            newChild->children[j] = child->children[j + t];
        }
    }
    child->size = t - 1;
    for (int j = parent->size; j > i; j--)
    {
        parent->children[j + 1] = parent->children[j];
    }
    parent->children[i + 1] = newChildOffset;
    for (int j = parent->size - 1; j >= i; j--)
    {
        parent->keys[j + 1] = parent->keys[j];
    }
    parent->keys[i] = child->keys[t - 1];
    parent->size = parent->size + 1;
}

template <typename K, int pageSize>
void BTree<K, pageSize>::insert(K key)
{
    if (read(rootOffset_)->size == 2 * t - 1)
    {
        long long newRootOffset = allocate();
        auto newRoot = read(newRootOffset);
        auto oldRoot = read(rootOffset_);
        newRoot->leaf = false;
        newRoot->size = 0;
        newRoot->children[0] = rootOffset_;
        rootOffset_ = newRootOffset;
        splitChild(rootOffset_, 0);
        insertNonfull(rootOffset_, key);
    }
    else
    {
        insertNonfull(rootOffset_, key);
    }
}

template <typename K, int pageSize>
void BTree<K, pageSize>::insertNonfull(long long nodeOffset, K key)
{
    auto node = read(nodeOffset);
    int i = node->size - 1;
    if (node->leaf)
    {
        while (i >= 0 && key < node->keys[i])
        {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->size++;
    }
    else
    {
        while (i >= 0 && key < node->keys[i])
        {
            i--;
        }

        if (read(node->children[i + 1])->size == (2 * t - 1))
        {
            splitChild(nodeOffset, i + 1);
            node = read(nodeOffset);
            if (key > node->keys[i + 1])
            {
                i++;
            }
        }
        insertNonfull(node->children[i + 1], key);
    }
}

template <typename K, int pageSize>
std::optional<K> BTree<K, pageSize>::search(long long nodeOffset, K key)
{
    int i = 0;

    auto node = read(nodeOffset);
    while (i < node->size && key > node->keys[i])
    {
        i++;
    }
    if (i < node->size && key == node->keys[i])
    {
        return node->keys[i];
    }
    else if (node->leaf)
        return std::nullopt;
    return search(node->children[i], key);
}

template <typename K, int pageSize>
std::optional<K> BTree<K, pageSize>::search(K key)
{
    return search(rootOffset_, key);
}

template <typename K, int pageSize>
long long BTree<K, pageSize>::getRootOffset()
{
    return rootOffset_;
}

template <typename K, int pageSize>
void BTree<K, pageSize>::swap(long long nodeOffset, K key, K newKey)
{
    int i = 0;
    auto node = read(nodeOffset);
    while (i < node->size && key > node->keys[i])
    {
        i++;
    }
    if (i < node->size && key == node->keys[i])
    {
        node->keys[i] = newKey;
        return;
    }
    else if (node->leaf)
        return;
    return swap(node->children[i], key, newKey);
}

template <typename K, int pageSize>
void BTree<K, pageSize>::swap(K key, K newKey)
{
    swap(rootOffset_, key, newKey);
}
#endif