cmake_minimum_required(VERSION 3.10.0)
project(Test VERSION 0.1.0 LANGUAGES C CXX)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src)

include_directories(${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/include)
find_package(UnitTest++ REQUIRED)

file(GLOB TEST_SOURCES "*.cpp")

add_executable(BtreeTests ${TEST_SOURCES})

target_link_libraries(BtreeTests btree_map btree_set allocator mappedFile metadata UnitTest++ )

add_test(NAME BtreeTests COMMAND BtreeTests)