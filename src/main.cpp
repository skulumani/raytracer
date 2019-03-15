#include "renderer.hpp"
#include "geometry.hpp"

int main() {
    
    // define different materials
    Material ivory(0.4, 0.4, 0.3);
    Material red_rubber(0.3, 0.1, 0.1);

    // define a sphere
    //
    Eigen::Vector3f center(0, 0, 10);
    float radius(1);
    Sphere sphere(center, radius);

    std::vector<Sphere> spheres;
    spheres.push_back(Sphere(-3,    0,   -16, 2,      ivory));
    spheres.push_back(Sphere(-1.0, -1.5, -12, 2, red_rubber));
    spheres.push_back(Sphere( 1.5, -0.5, -18, 3, red_rubber));
    spheres.push_back(Sphere( 7,    5,   -18, 4,      ivory));

    render(sphere); 
    return 0;
}
