#include "tb_type_traits.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Testing integral_constant", "[integral_constant]") {
    typedef tbSTL::integral_constant<int, 2> two_t;
    typedef tbSTL::integral_constant<int, 4> four_t;
    SECTION("Two integer") {
        REQUIRE(two_t::value * 2 == four_t::value);
    }
    SECTION("Function object") {
        REQUIRE(two_t() == 2);
    }
    SECTION("Type") {
        REQUIRE(tbSTL::is_same<two_t::value_type, int>::value == true);
    }
    SECTION("value_type") { // type conversion operator
        two_t two;
        four_t four;
        REQUIRE(two * two == four);
        REQUIRE(two + two == four);
    }
}

TEST_CASE("Testing bool_constant", "[bool_constant]") {
    SECTION("Bool type") {
        REQUIRE(tbSTL::is_same<tbSTL::true_type::value_type, bool>::value == true);
        REQUIRE(tbSTL::is_same<tbSTL::false_type::value_type, bool>::value == true);
    }
    SECTION("Bool value") {
        REQUIRE(tbSTL::true_type::value == true);
        REQUIRE(tbSTL::false_type::value == false);
    }
}

TEST_CASE("Testing is_trivally_bool", "[is_trival_bool]") {
    SECTION("is_trivally_default_constructible") {
        REQUIRE(tbSTL::is_trivally_default_constructible<bool>::value == true);
    }
    SECTION("is_trivally_copy_constructible") {
        REQUIRE(tbSTL::is_trivally_copy_constructible<bool>::value == true);
    }
    SECTION("is_trivally_move_constructible") {
        REQUIRE(tbSTL::is_trivally_move_constructible<bool>::value == true);
    }
    SECTION("is_trivally_copy_assignable") {
        REQUIRE(tbSTL::is_trivally_copy_assignable<bool>::value == true);
    }
    SECTION("is_trivally_move_assignable") {
        REQUIRE(tbSTL::is_trivally_move_assignable<bool>::value == true);
    }
    SECTION("is_trivally_destructible") {
        REQUIRE(tbSTL::is_trivally_destructible<bool>::value == true);
    }
}

TEST_CASE("Testing is_trivally_struct", "[is_trivally_struct") {
    struct Obj { };
    SECTION("is_trivally_default_constructible") {
        REQUIRE(tbSTL::is_trivally_default_constructible<Obj>::value == false);
    }
    SECTION("is_trivally_copy_constructible") {
        REQUIRE(tbSTL::is_trivally_copy_constructible<Obj>::value == false);
    }
    SECTION("is_trivally_move_constructible") {
        REQUIRE(tbSTL::is_trivally_move_constructible<Obj>::value == false);
    }
    SECTION("is_trivally_copy_assignable") {
        REQUIRE(tbSTL::is_trivally_copy_assignable<Obj>::value == false);
    }
    SECTION("is_trivally_move_assignable") {
        REQUIRE(tbSTL::is_trivally_move_assignable<Obj>::value == false);
    }
    SECTION("is_trivally_destructible") {
        REQUIRE(tbSTL::is_trivally_destructible<bool>::value == true);
    }
}

TEST_CASE("Testing remove_*", "[remove_*]") {
    SECTION("remove_const") {
        REQUIRE(tbSTL::is_same<tbSTL::remove_const<const bool>::type, bool>::value == true);
    }
    SECTION("remove_volatile") {
        REQUIRE(tbSTL::is_same<tbSTL::remove_volatile<volatile bool>::type, bool>::value == true);
    }
    SECTION("remove_cv") {
        REQUIRE(tbSTL::is_same<tbSTL::remove_cv<const volatile bool>::type, bool>::value == true);
    }
}

TEST_CASE("Testing is_integral", "[is_integral]") {
    SECTION("is_integral int") {
        REQUIRE(tbSTL::is_integral<int>::value == true);
    }
    SECTION("not_integral double") {
        REQUIRE(tbSTL::is_integral<double>::value == false);
    }
}