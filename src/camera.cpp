#include "camera.hpp"

// Camera object

Camera::Camera( void ) {
    
    m_position << 0, 0, 0;
    // camera frame axis defined in inertial frame
    m_view_axis << 0, 0, 1;
    m_up_axis << 0, 1, 0;
    m_right_axis << 1, 0, 0;

    /* fov_h = M_PI/3.0; */
    /* fov_w = M_PI/3.0; */
    
    m_focal << 554, 554;
    m_image_size << 640, 480;
    
    m_center = m_image_size / 2;

    // focal length
    /* const float dist(height / (2.0 * std::tan(fov_h/2.0))); */
     init();    
}

/* Eigen::Vector3f Camera::get_ray(const int& px, const int& py) const { */

/* } */

void Camera::init( void ) {
    // form intrinsic matrix
    extrinsic.block(0, 0, 3, 3) = Eigen::Matrix3f::Identity();
    extrinsic.col(3) = Eigen::Vector3f::Zero();

    // form extrinsic matrix
    intrinsic = Eigen::Matrix3f::Zero();
    intrinsic(0, 0) = m_focal(0);
    intrinsic(1, 1) = m_focal(1);
    intrinsic(2, 2) = 1;
    intrinsic(0, 2) = m_center(0);
    intrinsic(1, 2) = m_center(1);

}

Eigen::Vector3f Camera::get_position( void ) const {
    return m_position;
}

