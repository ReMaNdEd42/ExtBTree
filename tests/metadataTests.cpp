#include "allocator/helpers/metadata.h"
#include <UnitTest++/UnitTest++.h>

SUITE(Metadata)
{
    TEST(serialize_and_serialize)
    {
        json testJSON;
        testJSON = "testValue";

        Metadata::serialize(".", "test", testJSON);

        json extractedJSON = Metadata::deserialize(".", "test");

        CHECK_EQUAL(extractedJSON, "testValue");
    }
    
}