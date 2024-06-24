cmake_minimum_required(VERSION 3.10.0)
project(Main VERSION 0.1.0 LANGUAGES C CXX)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src)

list(APPEND METADATA_SRC allocator/helpers/metadata.cpp)
add_library(metadata STATIC ${METADATA_SRC})

list(APPEND MAPPEDFILE_SRC allocator/helpers/mappedFile.cpp)
add_library(mappedFile STATIC ${MAPPEDFILE_SRC})

list(APPEND ALLOCATOR_SRC allocator/poolAllocator.cpp)
add_library(allocator STATIC ${ALLOCATOR_SRC})

list(APPEND BTREE_SRC btree/btree.cpp)
add_library(btree STATIC ${BTREE_SRC})

list(APPEND BTREE_MAP container/btree_map.cpp)
add_library(btree_map STATIC ${BTREE_MAP})

list(APPEND BTREE_SET container/btree_set.cpp)
add_library(btree_set STATIC ${BTREE_SET})


target_link_libraries(btree allocator mappedFile metadata)

target_link_libraries(btree_map btree)
target_link_libraries(btree_set  btree)


add_library(btree::map ALIAS btree_map)
add_library(btree::set ALIAS btree_set)