#include "allocator/tb_construct.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Testing construct", "construct") {
    int *p = new int(0);
    int val = 10;

    tbSTL::construct(p, val);

    REQUIRE(*p == val);

    delete p;
}

TEST_CASE("Testing destroy", "destroy") {
    int *p = new int (0);
    int val = 10;

    tbSTL::construct(p, val);

    tbSTL::destroy(p);

    delete p;
}