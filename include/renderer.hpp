#ifndef RENDERER_H
#define RENDERER_H

#include <limits>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>

#include <Eigen/Core>

#include "geometry.hpp"
#include "camera.hpp"

// single color and sphere
void render( const Sphere& sphere );
void render( const Camera& cam, const Sphere& sphere);

// multiple spheres
void render(const std::vector<Sphere>& spheres);
void render(const Camera& cam, const std::vector<Sphere>& spheres);

// multiple spheres, lights and diffuse lighting
void render(const std::vector<Sphere>& spheres, const std::vector<Light>& lights);
void render( const Camera& cam, const std::vector<Sphere>& spheres, const std::vector<Light>& lights);

// multiple spheres and phong lighting model
void phong_render(const Camera& cam, 
        const std::vector<Sphere>& spheres, const std::vector<Light>& lights,
        const size_t depth=0);

#endif
