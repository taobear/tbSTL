#include "tb_type_traits.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("integral_constant testing", "[integral_constant]") {
    SECTION("Two integer") {
        typedef tbSTL::integral_constant<int, 2> two_t;
        typedef tbSTL::integral_constant<int, 4> four_t;

        // CHECK(two_t::value * 2 == four_t::value);
    }
    SECTION("Function object") {
        // CHECK(tbSTL::integral_constant<int, 2>() == 2);
    }
}

TEST_CASE("bool_constant testing", "[bool_constant]") {
    SECTION("Bool type") {
        CHECK(tbSTL::true_type::value == true);
        CHECK(tbSTL::false_type::value == false);
    }
}