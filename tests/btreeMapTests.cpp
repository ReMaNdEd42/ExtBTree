#include "container/btree_map.h"
#include "container/btree_map.cpp"
#include <UnitTest++/UnitTest++.h>
#include <iostream>

SUITE(BtreeMap)
{
    TEST(init_insert)
    {
        btree_map<int, int> btree_map_test(".");

        btree_map_test.insert({2, 5});
        btree_map_test.insert({3, 10});
        btree_map_test.insert({4, 15});

        int sum = 0;

        for (auto &i : btree_map_test.toMap())
        {
            CHECK_EQUAL((i.second % 5), 0);
            sum += i.second;
            sum += i.first;
        }
        CHECK_EQUAL(sum, 39);
    }
}