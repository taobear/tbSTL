#include "iterator/tb_iterbase.h"

#include <vector>
#include <list>
#include <forward_list>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Testing distance", "[distance]")
{
    SECTION("random distance") {
        std::vector<int> vec {1, 2, 3, 4};
        REQUIRE(tbSTL::distance(vec.end(), vec.begin()) == -4);
    }
    SECTION("input distance") {
        std::list<int> lst{1, 2, 3, 4};
        REQUIRE(tbSTL::distance(lst.begin(), lst.end()) == 4);
    }
}

TEST_CASE("Testing advance", "[advance]")
{
    SECTION("random advance") {
        std::vector<int> vec {1, 2, 3, 4};
        auto iter = vec.begin();
        tbSTL::advance(iter, 3);
        REQUIRE(*iter == 4);
    }

    SECTION("input advance") {
        std::forward_list<int> flt {1, 2, 3, 4};
        auto iter = flt.begin();
        tbSTL::advance(iter, 3);
        REQUIRE(*iter == 4);
    }

    SECTION("bidirect advance") {
        std::list<int> lst {1, 2, 3, 4};
        auto iter = lst.end();
        tbSTL::advance(iter, -3);
        REQUIRE(*iter == 2);
    }
}
