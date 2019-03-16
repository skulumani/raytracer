#ifndef RENDERER_H
#define RENDERER_H

#include <limits>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>

#include <Eigen/Core>

#include "geometry.hpp"

void render( const Sphere& sphere );
void render(const std::vector<Sphere>& spheres);
void render(const std::vector<Sphere>& spheres, const std::vector<Light>& lights);

void phong_render(const std::vector<Sphere>& spheres, const std::vector<Light>& lights);


#endif
