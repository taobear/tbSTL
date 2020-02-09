#include "allocator/tb_uninitialized.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>

TEST_CASE("Testing unitialized", "uninitialized_copy")
{
    std::vector<int> vec1(10, 2);
    std::vector<int> vec2(10);

    tbSTL::uninitialized_copy(vec1.begin(), vec1.end(), vec2.begin());
}