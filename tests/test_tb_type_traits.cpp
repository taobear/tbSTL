#include "tb_type_traits.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Testing integral_constant", "[integral_constant]") {
    SECTION("Two integer") {
        typedef tbSTL::integral_constant<int, 2> two_t;
        typedef tbSTL::integral_constant<int, 4> four_t;
        REQUIRE(two_t::value * 2 == four_t::value);
    }
    SECTION("Function object") {
        REQUIRE(tbSTL::integral_constant<int, 2>() == 2);
    }
}

TEST_CASE("Testing bool_constant", "[bool_constant]") {
    SECTION("Bool true") {
        REQUIRE(tbSTL::true_type::value == true);
        REQUIRE(tbSTL::false_type::value == false);
    }
}