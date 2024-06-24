#include <iostream>
#include "btree_map.h"
int main(int argc, char const *argv[])
{
    btree_map<int, int> btree_map_test(".");

    btree_map_test.insert({2, 5});
    btree_map_test.insert({3, 10});
    btree_map_test.insert({4, 15});

    int sum = 0;

    for (auto &i : btree_map_test.toMap())
    {
        sum += i.second;
        sum += i.first;
    }
    std::cout << "sum of values and keys: " << sum;
    return 0;
}