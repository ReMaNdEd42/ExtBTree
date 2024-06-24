cmake_minimum_required(VERSION 3.10.0)
project(Example VERSION 0.1.0 LANGUAGES C CXX)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(example main.cpp)

target_link_libraries(example btree::map)