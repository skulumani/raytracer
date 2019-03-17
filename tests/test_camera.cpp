#include "gtest/gtest.h"

#include <iostream>

#include "camera.hpp"

TEST(TestCamera, CameraDefaultConstructor) {
    Camera cam;
    ASSERT_TRUE(cam.get_position().isApprox(Eigen::Vector3f::Zero()));
    ASSERT_TRUE(cam.get_view_axis().isApprox((Eigen::Vector3f() << 0, 0, 1).finished()));
}

TEST(TestCamera, CameraNamedParameter) {
    Camera cam;
    cam.position((Eigen::Vector3f() << 1, 2, 3).finished());
    cam.focal((Eigen::Vector2f() << 600, 600).finished());
    ASSERT_TRUE(cam.get_position().isApprox((Eigen::Vector3f() << 1, 2, 3).finished()));
    ASSERT_TRUE(cam.get_image_size().isApprox((Eigen::Vector2i() << 692, 692).finished()));
}
