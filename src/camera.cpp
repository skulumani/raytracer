#include <iostream>
#include <assert.h>

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

int Camera::get_pixel( const Eigen::Ref<const Eigen::Vector3f>& ray,
        Eigen::Ref<Eigen::Vector2f> pixel) const {
    // forward transformation vector in camera frame to pixel location
    // needs to be infront of camera

    /* assert( ray(2) > 0 ); */
    // make sure pixel is within image plane
    
    if (ray(2) <= 0) {
        // behind the image plane
        pixel << -1, -1;
        return -1;
    } else {
        // make a homegeneous vector
        Eigen::Vector4f cam_vec;
        cam_vec << ray, 1;
        Eigen::Vector3f pixel_homogenous = m_intrinsic * m_extrinsic * cam_vec;
        pixel = pixel_homogenous.head(2) / pixel_homogenous(2);
    }

    if (pixel(0) > m_image_size(0)/2 || pixel(1) > m_image_size(1)/2 || 
            pixel(0) < -m_image_size(0)/2 || pixel(1) < -m_image_size(1)/2) {
        return -2;
    } else {
        return 0;
    }
}

int Camera::get_pixel(const float& rx, const float& ry, const float& rz,
        Eigen::Ref<Eigen::Vector2f> pixel) const {
    Eigen::Vector3f ray(rx, ry, rz);
    int success = this->get_pixel(ray, pixel);
    return success;
}

int Camera::get_ray( const Eigen::Ref<const Eigen::Vector2f>& p_in,
        Eigen::Ref<Eigen::Vector3f> ray) const {
    // pixel within image frame
    if (p_in(0) > m_image_size(0) || p_in(1) > m_image_size(1) ||
            p_in(0) < 0 || p_in(1) < 0) {
        ray = Eigen::Vector3f::Zero();
        return -1;
    } else {
        Eigen::Vector3f pixel_homogenous(p_in(0), p_in(1), 1);
        ray = m_intrinsic.inverse() * pixel_homogenous;
        ray.normalize();
        return 0;
    }
}

int Camera::get_ray(const float& px, const float& py,
        Eigen::Ref<Eigen::Vector3f> ray) const {
    Eigen::Vector2f p_in(px, py);
    int success = this->get_ray(p_in, ray);
    return success;
}
