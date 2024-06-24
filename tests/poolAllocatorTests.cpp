#include "allocator/poolAllocator.h"
#include "allocator/helpers/mappedFile.h"
#include <memory>
#include <UnitTest++/UnitTest++.h>

SUITE(PoolAllocator_with_mappedFIle)
{
    TEST(allocate_and_dellocate)
    {
        std::unique_ptr<MappedFile> mf = std::make_unique<MappedFile>("testMappedFile");

        PoolAllocator pa(mf.get());

        auto addr = pa.allocate();
        pa.dellocate(addr);
        CHECK(true);
    }
}