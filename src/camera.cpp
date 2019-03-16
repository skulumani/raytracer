#include "camera.hpp"

// Camera object

Camera::Camera( void ) {

    width = 640;
    height = 480;
    
    fov_h = M_PI/3.0;
    fov_w = M_PI/3.0;

    // focal length
    const float dist(height / (2.0 * std::tan(fov_h/2.0)));
    
    // camera frame axis defined in inertial frame
    view_axis << 0, 0, 1;
    up_axis << 0, 1, 0;
    right_axis << 1, 0, 0;

    const Eigen::Vector3f view_axis(0, 0, 1);
    const Eigen::Vector3f up_axis(0, 1, 0);
    const Eigen::Vector3f right_axis(1, 0, 0);
    const Eigen::Vector3f cam_axis(0, 0, dist);
}
