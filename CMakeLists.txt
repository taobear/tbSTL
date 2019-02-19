cmake_minimum_required(VERSION 3.10)
project(tbSTL)

set(CMAKE_CXX_STANDARD 14)

include_directories(./ include)
add_executable(test_tb_type_traits tests/test_tb_type_traits.cpp)