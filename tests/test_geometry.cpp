#include "gtest/gtest.h"

#include "geometry.hpp"

TEST(TestGeometry, Vec2IntConstructor) {
    // default constructor
    Vec<2, int> vec_int;
    
    ASSERT_EQ(1, 1);
}

TEST(TestGeometry, Vec2IntConstructorValues) {
    Vec<2, int> vec_int(1, 2);

    ASSERT_EQ(vec_int[0], 1);
    ASSERT_EQ(vec_int[1], 2);
}
