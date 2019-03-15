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

// Material class
Material::Material( void ) {
    diffuse_color = Eigen::Vector3f::Random().cwiseAbs();
}

Material::Material(const Eigen::Ref<const Eigen::Vector3f>& color) {
    diffuse_color = color;
}

Material::Material(const float& r_in, const float& g_in, const float& b_in) {
    diffuse_color << r_in, g_in, b_in;
}

Eigen::Vector3f Material::get_diffuse( void ) {
    return this->diffuse_color;
}

// Lights
Light::Light( void ) {
    position << 0, -10, 0;
    intensity = 1;
}

Light::Light( const Eigen::Ref<const Eigen::Vector3f>& pos_in,
        const float& int_in) {
    position = pos_in;
    intensity = int_in;
}

// Sphere class
Sphere::Sphere( void ) {
    center << 0.0, 0.0, 0.0;
    radius = 1.0;
}

Sphere::Sphere(const float& xc_in, const float& yc_in,
        const float& zc_in, const float& r_in) {
    center << xc_in, yc_in, zc_in;
    radius = r_in;
}

Sphere::Sphere(const float& xc_in, const float& yc_in,
        const float& zc_in, const float& radius_in, const Material& m_in) {
    center << xc_in, yc_in, zc_in;
    radius = radius_in;
    material = m_in;
}

Sphere::Sphere(const Eigen::Ref<const Eigen::Vector3f>& center_in,
        const float& radius_in) {
    center = center_in;
    radius = radius_in;
}

Sphere::Sphere(const Eigen::Ref<const Eigen::Vector3f>& center_in, 
        const float& radius_in, const Material& m_in) {
    center = center_in;
    radius = radius_in;
    material = m_in;
}

Material Sphere::get_material( void ) const {
    return this->material;
}

bool Sphere::ray_intersect(const Eigen::Vector3f& origin, const Eigen::Vector3f& view_direction, float& dist) const {
    // Look here : https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
    // or here: https://github.com/ssloy/tinyraytracer/commit/5806eb45e93dab225ab335824cbc3f537d511b28
    // TODO Derive and rewrite this ray and sphere intersect function
    // vector from origin to center of sphere
    Eigen::Vector3f origin_to_center = this->center - origin;
    
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
    float tca = origin_to_center.dot(view_direction);
    float d2 = origin_to_center.dot(origin_to_center) - tca*tca;
    if (d2 > radius*radius) return false;

    float thc = sqrtf(radius*radius - d2);
    dist       = tca - thc;
    float t1 = tca + thc;
    if (dist < 0) dist = t1;
    if (dist < 0) return false;

    return true;
}

Eigen::Vector3f cast_ray(const Eigen::Ref<const Eigen::Vector3f>& orig, 
        const Eigen::Ref<const Eigen::Vector3f>& dir, const Sphere &sphere) {
    float sphere_dist = std::numeric_limits<float>::max();
    // cast ray from origin to infinity
    if (!sphere.ray_intersect(orig, dir, sphere_dist)) {
        return (Eigen::Vector3f() << 0.2, 0.7, 0.8).finished(); // background color
    }
    return sphere.get_material().get_diffuse(); // color of sphere
}

Eigen::Vector3f cast_ray(const Eigen::Ref<const Eigen::Vector3f>& orig,
        const Eigen::Ref< const Eigen::Vector3f>& dir,
        const std::vector<Sphere>& spheres) {
    // set maximum distance
    float sphere_dist = std::numeric_limits<float>::max();
    Eigen::Vector3f color(0.2, 0.7, 0.8);
    // loop over each sphere and check if intersect
    for (size_t ii = 0; ii < spheres.size(); ii++) {
        // need to find sphere with minimum distance and output that color
        float dist_i; // gets modified inside function
        if (spheres[ii].ray_intersect(orig, dir, dist_i) && dist_i < sphere_dist) {
            sphere_dist = dist_i;
            color = spheres[ii].get_material().get_diffuse(); 
        }
    }
    return color;
}

Eigen::Vector3f cast_ray(const Eigen::Ref<const Eigen::Vector3f>& orig,
        const Eigen::Ref< const Eigen::Vector3f>& dir,
        const std::vector<Sphere>& spheres,
        const std::vector<Light>& lights) {
    // set maximum distance
    float sphere_dist = std::numeric_limits<float>::max();
    Eigen::Vector3f color(0.2, 0.7, 0.8);
    // loop over each sphere and check if intersect
    for (size_t ii = 0; ii < spheres.size(); ii++) {
        // need to find sphere with minimum distance and output that color
        float dist_i; // gets modified inside function
        if (spheres[ii].ray_intersect(orig, dir, dist_i) && dist_i < sphere_dist) {
            sphere_dist = dist_i;
            color = spheres[ii].get_material().get_diffuse(); 
        }
    }
    return color;
}

