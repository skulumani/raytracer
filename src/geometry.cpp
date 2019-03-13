#include "geometry.hpp"

// members for Vec class
template<size_t DIM, typename T>
Vec<DIM, T>::Vec( void ) {
    for (size_t ii=DIM; ii--; _data[ii] = T());
}

template<size_t DIM, typename T>
T& Vec<DIM, T>::operator [] (const size_t ii) {
    assert(ii < DIM);
    return _data[ii];
}

template<size_t DIM, typename T>
const T& Vec<DIM, T>::operator [] (const size_t ii) const {
    assert(ii < DIM);
    return _data[ii];
}

// Vec<2, T> class
/* template<typename T> */
/* Vec<2, T>::Vec( void ) { */
/*     x = T(); */
/*     y = T(); */
/* } */

/* template<typename T> */
/* Vec<2, T>::Vec(T X, T Y) { */
/*     x = X; */
/*     y = Y; */
/* } */

/* template <> class Vec<2, int>; */


// Sphere class
Sphere::Sphere( void ) {
    center = Vec3f(0.0, 0.0, 0.0);
    radius = 1.0;
}

Sphere::Sphere(const float & xc_in, const float& yc_in, const float& zc_in, const float& r_in) {
    center = Vec3f(xc_in, yc_in, zc_in);
    radius = r_in;
}

Sphere::Sphere(const Vec3f& center_in, const float& radius_in) {
    center = center_in;
    radius = radius_in;
}

bool Sphere::ray_intersect(const Vec3f& origin, const Vec3f& view_direction, float& t0) {
    // vector from origin to center of sphere
    Vec3f origin_to_center = this->center - origin;
    
    /* // check dot product of origin2center and view_direction */
    /* float dot_product = origin_to_center * view_direction; */

    /* if (dot_product < 0) { */
    /*     // view direction is away from the sphere */
    /*     float dist_origin_to_center = origin_to_center.norm(); */
    /*     if ( dist_origin_to_center > radius) { */
    /*         return false; */
    /*     } else if ( dist_origin_to_center == radius) { */
    /*         return true; */
    /*     } else { */
    /*        // origin is inside the sphere */

    /*     } */
    /* } else { */

    /* } */
    // dot product of vector to center and view direction
    float tca = origin_to_center*view_direction;
    float d2 = origin_to_center*origin_to_center - tca*tca;
    if (d2 > radius*radius) return false;

    float thc = sqrtf(radius*radius - d2);
    t0       = tca - thc;
    float t1 = tca + thc;
    if (t0 < 0) t0 = t1;
    if (t0 < 0) return false;

    return true;
}

