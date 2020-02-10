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

