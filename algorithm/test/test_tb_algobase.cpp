#include "algorithm/tb_algobase.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <cmath>

template <class T> class Compare {
public:
    static bool IsEqual(const T &lh, const T &rh) {
        return lh == rh;
    }
};

template <> class Compare<float> {
public:
    static bool IsEqual(const float &lh, const float &rh) {
        return abs(lh - rh) < 10e-3;
    }
};

template <> class Compare<double> {
public:
    static bool IsEqual(const double &lh, const double &rh) {
        return abs(lh - rh) < 10e-6;
    }
};

TEST_CASE("Compare", "IsEqual") 
{
    REQUIRE(Compare<int>::IsEqual(10, 10) == true);
    REQUIRE(Compare<float>::IsEqual(0.0001f, 0.0002f) == true); 
    REQUIRE(Compare<double>::IsEqual(0.00000001, 0.00000002) == true);
}

TEST_CASE("tb_algobase_01", "copy")
{
    int in[] = {1, 2, 3};
    int out[4] = { 0 };
    tbSTL::copy(in, in + 3, out);

    for (int i = 0; i < sizeof(in) / sizeof(int); ++i) {
        REQUIRE(in[i] == out[i]);
    }

    REQUIRE(out[3] == 0);
}

TEST_CASE("tb_algobase_02", "fill")
{
    int dest[4];
    tbSTL::fill(dest, dest + 4, 10);

    for (int i = 0; i < 4; ++i) {
        REQUIRE(dest[i] == 10);
    }
}

TEST_CASE("tb_algobase_03", "copy_n")
{
    int in[] = {1, 2, 3};
    int out[4] = { 0 };
    tbSTL::copy_n(in, sizeof(in) / sizeof(int), out);

    for (int i = 0; i < sizeof(in) / sizeof(int); ++i) {
        REQUIRE(in[i] == out[i]);
    }

    REQUIRE(out[3] == 0);
}

TEST_CASE("tb_algobase_04", "fill_n")
{
    int dest[4];
    tbSTL::fill_n(dest, sizeof(dest) / sizeof(int), 10);

    for (int i = 0; i < 4; ++i) {
        REQUIRE(dest[i] == 10);
    }
}