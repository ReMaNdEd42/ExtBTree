#include "allocator/helpers/mappedFile.h"
#include <UnitTest++/UnitTest++.h>

SUITE(MappedFile)
{
    TEST(open_and_resize)
    {
        MappedFile mp("testMappedFile");
        mp.resize(10);
        CHECK_EQUAL(mp.getSize(), 10);
    }
}