cmake_minimum_required(VERSION 3.10)
project(tbSTL)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g") 

include_directories(./ include)

add_subdirectory(tests)