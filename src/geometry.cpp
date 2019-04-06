#include <algorithm>

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
    ambient_color = diffuse_color;
    specular_color = (Eigen::Vector3f() << 1, 1, 1).finished();

    albedo << 0.5, 0.5, 0;
    specular_constant = 10;
}

Material::Material(const Eigen::Ref<const Eigen::Vector3f>& color) {
    diffuse_color = color;
    ambient_color = color;
    specular_color = (Eigen::Vector3f() << 1, 1, 1).finished();

    albedo << 0.9, 0.1, 0;
    specular_constant = 10;
}

Material::Material(const float& r_in, const float& g_in, const float& b_in) {
    diffuse_color << r_in, g_in, b_in;
    ambient_color = diffuse_color;
    specular_color = (Eigen::Vector3f() << 1, 1, 1).finished();

    albedo << 0.6, 0.4, 0;
    specular_constant = 50;
}

Material::Material(const Eigen::Ref<const Eigen::Vector3f>& albedo_in,
        const Eigen::Ref<const Eigen::Vector3f>& color,
        const float& spec) {
    diffuse_color = color;
    ambient_color = color;
    specular_color = (Eigen::Vector3f() << 1, 1, 1).finished();

    albedo = albedo_in;
    specular_constant = spec;
}

Eigen::Vector3f Material::get_diffuse( void ) {
    return this->diffuse_color;
}

Eigen::Vector3f Material::get_specular( void ) {
    return this->specular_color;
}

Eigen::Vector3f Material::get_albedo( void ) {
    return this->albedo;
}

float Material::get_specular_constant( void ) {
    return this->specular_constant;
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

Eigen::Vector3f Light::get_position( void ) const {
    return this->position;
}

float Light::get_itensity( void ) const {
    return this->intensity;
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

Eigen::Vector3f Sphere::get_center( void ) const {
    return this->center;
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

bool scene_intersection(const Eigen::Ref<const Eigen::Vector3f>& origin,
        const Eigen::Ref<const Eigen::Vector3f>& direction,
        const std::vector<Sphere>& spheres,
        Eigen::Ref<Eigen::Vector3f> hit,
        Eigen::Ref<Eigen::Vector3f> normal,
        Material& material,
        bool& background) {

    float sphere_dist = std::numeric_limits<float>::max();
    Eigen::Vector3f color;

    for (size_t ii = 0; ii < spheres.size(); ii++) {
        // need to find sphere with minimum distance and output that color
        float dist_i; // gets modified inside function
        if (spheres[ii].ray_intersect(origin, direction, dist_i) && dist_i < sphere_dist) {
            sphere_dist = dist_i;
            hit = origin + dist_i * direction;
            normal = (hit - spheres[ii].get_center()).normalized();
            color = spheres[ii].get_material().get_diffuse(); 
            material = spheres[ii].get_material();
            background = false;
        }
    }

    return sphere_dist<1000;
}

Eigen::Vector3f cast_ray(const Eigen::Ref<const Eigen::Vector3f>& orig,
        const Eigen::Ref< const Eigen::Vector3f>& dir,
        const std::vector<Sphere>& spheres,
        const std::vector<Light>& lights,
        const size_t depth) {
    bool background = true;

    // set maximum distance
    float sphere_dist = std::numeric_limits<float>::max();
    Eigen::Vector3f color;
    Material material;

    Eigen::Vector3f hit, normal;
    scene_intersection(orig, dir, spheres, hit, normal, material, background);

    // loop over each sphere and check if intersect
    /* for (size_t ii = 0; ii < spheres.size(); ii++) { */
    /*     // need to find sphere with minimum distance and output that color */
    /*     float dist_i; // gets modified inside function */
    /*     if (spheres[ii].ray_intersect(orig, dir, dist_i) && dist_i < sphere_dist) { */
    /*         sphere_dist = dist_i; */
    /*         hit = orig + dist_i * dir; */
    /*         normal = (hit - spheres[ii].get_center()).normalized(); */
    /*         color = spheres[ii].get_material().get_diffuse(); */ 
    /*         material = spheres[ii].get_material(); */
    /*         background = false; */
    /*     } */
    /* } */
    
    if (depth>4 || background) {
        return (Eigen::Vector3f() << 0.2, 0.7, 0.8).finished();
    } else {
        // modify the color based on normal.dot(light) intensity
        // loop over lights and compute dot product
        Eigen::Vector3f light_dir;
        float light_distance;
        float diffuse_light_intensity = 0;
        float specular_light_intensity = 0;
        
        Eigen::Vector3f reflect_dir = reflection(-dir, normal).normalized();
        Eigen::Vector3f reflect_origin;
        if ((float)reflect_dir.dot(normal) < 0) {
            reflect_origin = hit - normal * 1e-3;
        } else {
            reflect_origin = hit + normal * 1e-3;
        }
        Eigen::Vector3f reflect_color = cast_ray(reflect_origin, reflect_dir, spheres, lights, depth+1);

        for (size_t ii = 0; ii < lights.size(); ii++) {
            light_dir = (lights[ii].get_position() - hit).normalized();
            light_distance = (lights[ii].get_position() - hit).norm();
            /* Eigen::Vector3f shadow_orig = (float)light_dir.dot(normal) < 0 ? hit - normal*1e-3 : hit + normal*1e-3; // checking if the point lies in the shadow of the lights[i] */
            Eigen::Vector3f shadow_origin;
            if ((float)light_dir.dot(normal) < 0) {
                shadow_origin = hit - normal * 1e-3;
            } else {
                shadow_origin = hit + normal * 1e-3;
            }

            Eigen::Vector3f shadow_pt, shadow_normal;
            Material tmp_material;
            bool tmp_background;
            if (scene_intersection(shadow_origin, light_dir, spheres, shadow_pt, shadow_normal, tmp_material, tmp_background) &&
                    (shadow_pt - shadow_origin).norm() < light_distance) {
                continue;
            }

            diffuse_light_intensity += lights[ii].get_itensity() * std::max(0.0f, (float)(light_dir.dot(normal)));
            specular_light_intensity += powf(std::max(0.0f, reflection(-light_dir, normal).dot(dir)), 
                                             material.get_specular_constant()) * lights[ii].get_itensity();
        }

        return material.get_diffuse() * diffuse_light_intensity * material.get_albedo()(0) +
            material.get_specular() * specular_light_intensity * material.get_albedo()(1) +
            reflect_color * material.get_albedo()(2);
    }
}

Eigen::Vector3f reflection(const Eigen::Ref< const Eigen::Vector3f>& light, 
        const Eigen::Ref< const Eigen::Vector3f>& normal) {
    Eigen::Vector3f reflect;
    // assumes unit vectors
    reflect = 2 * light.dot(normal)* normal - light;
    return reflect;
}

