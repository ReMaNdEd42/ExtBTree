// TODO: - change checking according to struct alignment;
//       - fix remove() with implemetns of mergeChildren() and transferChildrenKey();
//       - move swap() to btreeAlgoritms;

#ifndef __BTREE_H_
#define __BTREE_H_
#include "allocator/allocator.h"
#include <optional>
#include <new>

template <typename K, int t>
struct Node
{
    K keys[2 * t - 1];
    long long children[2 * t];
    int size;
    bool leaf;
};

template <typename K, int pageSize, int t = 1>
constexpr int check_t() {
    if constexpr (sizeof(Node<K, t>) > pageSize) {
        return t - 1;
    } else {
        return check_t<K, pageSize, t + 1>();
    }
}

template <typename K, int pageSize = 4096>
class BTree
{
public:
    BTree(Allocator *allocator, long long rootOffset);

    BTree(Allocator *allocator);

    void insert(K key);

    void swap(K key, K newKey);

    std::optional<K> search(K key);

    // void remove(K key);

    long long getRootOffset();

private:
    static constexpr int t = check_t<K, pageSize>();

    Allocator *allocator_;

    long long rootOffset_;

    Node<K, t> *read(long long nodeOffset);

    long long allocate();

    void dellocate(long long nodeOffset);

    void create();

    void splitChild(long long parentOffset, int i);

    friend class BtreeAlgorithm;

    void insertNonfull(long long nodeOffset, K key);

    std::optional<K> search(long long nodeOffset, K key);

    void swap(long long nodeOffset, K key, K newKey);

    // long long mergeChildren(long long parentOffset, int i);

    // long long transferChildrenKey(long long parentOffset, int i);

    // void remove(long long nodeOffset, K key);
};
#endif // __BTREE_H_