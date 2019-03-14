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

TEST(TestGeometry, SphereConstructor) {
    Eigen::Vector3f center(-1, 0, 0);
    float radius(0.1);
    Sphere sphere(center, radius);
    ASSERT_EQ(1, 1);
}

TEST(TestGeometry, CastRayMiss) {
    Eigen::Vector3f origin(0, 0, 0);
    Eigen::Vector3f ray_vec(1, 0, 0);
    
    // make a sphere
    Eigen::Vector3f center(-1, 0, 0);
    float radius(0.1);
    Sphere sphere(center, radius);
    
    Eigen::Vector3f color;
    color = cast_ray(origin, ray_vec, sphere);
    ASSERT_EQ(color, (Eigen::Vector3f() << 0.2, 0.7, 0.8).finished());
}
