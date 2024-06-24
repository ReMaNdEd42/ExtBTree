#ifndef __BTREE_PAIR_H__
#define __BTREE_PAIR_H__
template <typename T1, typename T2>
class pair
{
public:
    T1 first;
    T2 second;

    bool operator==(const pair<T1, T2> &other) const
    {
        return first == other.first;
    }

    bool operator!=(const pair<T1, T2> &other) const
    {
        return !(*this == other);
    }

    bool operator<(const pair<T1, T2> &other) const
    {
        return first < other.first;
    }

    bool operator>(const pair<T1, T2> &other) const
    {
        return other < *this;
    }

    bool operator<=(const pair<T1, T2> &other) const
    {
        return !(other < *this);
    }

    bool operator>=(const pair<T1, T2> &other) const
    {
        return !(*this < other);
    }
};

#endif // __BTREE_PAIR_H__