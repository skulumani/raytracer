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

bool Sphere::ray_intersect() {
    return true;
}

