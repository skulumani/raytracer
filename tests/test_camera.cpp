#include "gtest/gtest.h"

#include "camera.hpp"

TEST(TestCamera, CameraDefaultConstructor) {
    Camera cam;
    ASSERT_TRUE(cam.get_position().isApprox(Eigen::Vector3f::Zero()));
    ASSERT_TRUE(cam.get_view_axis().isApprox((Eigen::Vector3f() << 0, 0, 1).finished()));
}
