#define private public
#include "allocator/tb_alloc.h"
#undef private

#include "allocator/tb_construct.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"


TEST_CASE("Testing Simple_alloc", "[simple_alloc]")
{
    tbSTL::simple_alloc<int, tbSTL::__malloc_alloc> alloc;

    int *p = alloc.allocate();
    tbSTL::construct(p, 10);

    REQUIRE(*p == 10);

    tbSTL::destroy(p);
    alloc.deallocate(p);
}

TEST_CASE("Testing __default_alloc_00", "[default_alloc]")
{
    REQUIRE(tbSTL::__default_alloc::ROUND_UP(1) == 8);
    REQUIRE(tbSTL::__default_alloc::ROUND_UP(10) == 16);
    REQUIRE(tbSTL::__default_alloc::ROUND_UP(100) == 104);

    REQUIRE(tbSTL::__default_alloc::FREELIST_INDEX(1) == 0);
    REQUIRE(tbSTL::__default_alloc::FREELIST_INDEX(10) == 1);
    REQUIRE(tbSTL::__default_alloc::FREELIST_INDEX(100) == 12);
}

TEST_CASE("Testing __default_alloc_01", "[default_alloc]")
{
    tbSTL::__default_alloc alloc;

    void *new_addr1 = alloc.allocate(10);
    REQUIRE(tbSTL::__default_alloc::get_list_num(10) == 19);
    REQUIRE(tbSTL::__default_alloc::end_free - tbSTL::__default_alloc::start_free == 20 * 16);

    void *new_addr2 = alloc.allocate(20);
    REQUIRE(tbSTL::__default_alloc::get_list_num(20) == 20 * 16 / 24 - 1);
    REQUIRE(tbSTL::__default_alloc::end_free - tbSTL::__default_alloc::start_free == 20 * 16 % 24);

    void *new_addr3 = alloc.allocate(1);
    REQUIRE(tbSTL::__default_alloc::get_list_num(1) == 0);
    REQUIRE(tbSTL::__default_alloc::end_free - tbSTL::__default_alloc::start_free == 0);
}