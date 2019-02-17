#include "tb_type_traits.h"
#include <iostream>
using namespace tbSTL;

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Testing integral_constant") {
    SECTION("Two integer") {
        typedef tbSTL::integral_constant<int, 2> two_t;
        typedef tbSTL::integral_constant<int, 4> four_t;

        static_assert(two_t::value * 2 == four_t::value,
                      "2*2 != 4");
    }
    SECTION("Print integer") {
        std::cout << tbSTL::integral_constant<int, 2>() << std::endl;
    }
}

TEST_CASE("Testing bool_constant") {
    SECTION("Bool true") {
        std::cout << tbSTL::true_type() << std::endl;
    }
}