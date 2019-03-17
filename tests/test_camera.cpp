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

TEST(TestCamera, RelativeWorldtoPixelOrigin) {
    Camera cam;
    Eigen::Vector3f world_pos;
    world_pos = cam.get_view_axis();
    Eigen::Vector2f pixel;
    int success = cam.get_pixel(world_pos, pixel);
    ASSERT_EQ(success, 0);
    ASSERT_TRUE(pixel.isApprox(cam.get_center().cast<float>()));
}

TEST(TestCamera, RelativeWorldtoPixelOriginScaled) {
    Camera cam;
    Eigen::Vector3f cam_vec;
    cam_vec = 10*cam.get_view_axis();
    Eigen::Vector2f pixel;
    int success = cam.get_pixel(cam_vec, pixel);
    ASSERT_EQ(success, 0);
    ASSERT_TRUE(pixel.isApprox(cam.get_center().cast<float>()));
}

TEST(TestCamera, RelativeWorldtoPrixelBehind) {
    Camera cam;
    cam.position((Eigen::Vector3f() << 1, 2, 3).finished());
    Eigen::Vector3f cam_vec(0, 0, -1); // vector in camera frame
    Eigen::Vector2f pixel;
    int success = cam.get_pixel(cam_vec, pixel);
    ASSERT_EQ(success, -1);
}

TEST(TestCamera, RelativeWorldtoPixelOffImage) {
    Camera cam;
    Eigen::Vector3f cam_vec;
    cam_vec << 10, 0, 0.1;
    Eigen::Vector2f pixel;
    int success = cam.get_pixel(cam_vec, pixel);
    ASSERT_EQ(success, -2);
}

TEST(TestCamera, PixeltoRelativeRayCenter) {
    Camera cam;
    Eigen::Vector2f pixel(320, 240);
    Eigen::Vector3f ray;
    int success = cam.get_ray(pixel, ray);
    ASSERT_EQ(success, 0);
    ASSERT_TRUE(ray.isApprox(cam.get_view_axis()));
}

TEST(TestCamera, PixeltoRelativeRayOffImage) {
    Camera cam;
    Eigen::Vector2f pixel(1000, 1000);
    Eigen::Vector3f ray;
    int success = cam.get_ray(pixel, ray);
    ASSERT_EQ(success, -1);
}
