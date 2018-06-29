cmake_minimum_required(VERSION 3.0)

project(LazyTuple)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Functional test
add_executable(lazy_tuple_test lazy_tuple.h lazy_tuple_test.cpp)
