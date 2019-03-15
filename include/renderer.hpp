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

struct Light {
    private:
        Eigen::Vector3f position;
        float intensity;

    public:
        Light(const Eigen::Ref<const Eigen::Vector3f>& pos_in,
                const float& int_in);
        Light( void );

};

#endif
