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
    m_image_size << 640, 480;
    m_focal(0) = m_image_size(0) / ( 2.0 * std::tan(m_fov(0) / 2.0));
    m_focal(1) = m_image_size(1) / ( 2.0 * std::tan(m_fov(1) / 2.0));
    
    m_center = m_image_size / 2;

    // focal length computation from FOV
    /* const float dist(height / (2.0 * std::tan(fov_h/2.0))); */
     init();    
}

/* Eigen::Vector3f Camera::get_ray(const int& px, const int& py) const { */

/* } */

void Camera::init( void ) {
    // form intrinsic matrix
    m_extrinsic.block(0, 0, 3, 3) = Eigen::Matrix3f::Identity();
    m_extrinsic.col(3) = Eigen::Vector3f::Zero();

    // form extrinsic matrix
    m_intrinsic = Eigen::Matrix3f::Zero();
    m_intrinsic(0, 0) = m_focal(0);
    m_intrinsic(1, 1) = m_focal(1);
    m_intrinsic(2, 2) = 1;
    m_intrinsic(0, 2) = m_center(0);
    m_intrinsic(1, 2) = m_center(1);

}

Eigen::Vector3f Camera::get_position( void ) const {
    return m_position;
}

Eigen::Vector3f Camera::get_view_axis( void ) const {
    return m_view_axis;
}

Eigen::Vector3f Camera::get_up_axis( void ) const {
    return m_up_axis;
}

Eigen::Vector3f Camera::get_right_axis( void ) const {
    return m_right_axis;
}

Eigen::Vector2f Camera::get_focal( void ) const {
    return m_focal;
}

Eigen::Vector2i Camera::get_image_size( void ) const {
    return m_image_size;
}

Eigen::Vector2i Camera::get_center( void ) const {
    return m_center;
}

Eigen::Matrix<float, 3, 4> Camera::get_extrinsic( void ) const {
    return m_extrinsic;
}

Eigen::Matrix3f Camera::get_intrinsic( void ) const {
    return m_intrinsic;
}

Eigen::Vector2f Camera::get_pixel( const Eigen::Ref<const Eigen::Vector3f>& ray) const {
    // forward transformation world to cam
    return Eigen::Vector2f::Zero();
}
