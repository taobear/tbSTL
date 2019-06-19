#include "iterator/tb_iterator.h"

#include <list>
#include <vector>
#include <algorithm>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"


TEST_CASE("Testing back_insert_iterator", "[back_insert_iterator]")
{
    typedef std::vector<int> IntVec;
    typedef std::list<int>   IntLst;

    IntVec vec = {0, 2, 3, 4};
    IntLst lst;

    tbSTL::back_insert_iterator<IntLst> biIter(lst);
    std::copy(vec.begin(), vec.end(), biIter);

    REQUIRE(std::equal(vec.begin(), vec.end(), lst.begin(), lst.end()));
}

TEST_CASE("Testing front_insert_iterator", "[front_insert_iterator]")
{
    typedef std::vector<int> IntVec;
    typedef std::list<int>   IntLst;

    IntVec vec = {0, 2, 3, 4};
    IntLst lst;

    tbSTL::front_insert_iterator<IntLst> fiIter(lst);
    std::copy(vec.begin(), vec.end(), fiIter);

    REQUIRE(std::equal(vec.begin(), vec.end(), lst.rbegin(), lst.rend()));
}

TEST_CASE("Testing insert_iterator", "[insert_iterator]")
{
    typedef std::vector<int> IntVec;
    typedef std::list<int> IntLst;

    IntVec vec = {0, 2, 3, 4};
    IntLst lst = {1, 2};
    IntVec vecExp = {1, 2, 0, 2, 3, 4};

    tbSTL::insert_iterator<IntLst> inIter(lst, lst.end());
    std::copy(vec.begin(), vec.end(), inIter);

    REQUIRE(std::equal(lst.begin(), lst.end(), vecExp.begin(), vecExp.end()));
}

TEST_CASE("Testing reverse_iterator", "[reverse_iterator]")
{
    typedef std::vector<int> IntVec;
    typedef std::vector<int>::iterator Iterator;

    IntVec vec = {0, 2, 3, 4};

    tbSTL::reverse_iterator<IntVec::iterator> rit(vec.end());
    REQUIRE(*rit == 4);
    REQUIRE(*(rit + 1) == 3);
    REQUIRE(*(rit + 2) == 2);

    REQUIRE(*(++rit) == 3);
    REQUIRE(*(++rit) == 2);

    REQUIRE(*(--rit) == 3);
    REQUIRE(*(--rit) == 4);

    rit += 2;
    REQUIRE(*rit == 2);

    rit -= 2;
    REQUIRE(*rit == 4);

    REQUIRE(rit[1] == 3);
    REQUIRE(rit[2] == 2);
}