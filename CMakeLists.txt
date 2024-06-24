cmake_minimum_required(VERSION 3.10.0)
project(Btree VERSION 0.1.0 LANGUAGES C CXX)

enable_testing()

add_subdirectory(example)
add_subdirectory(tests)
add_subdirectory(src)