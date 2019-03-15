#include "renderer.hpp"
#include "geometry.hpp"

int main() {
    
    // define different materials
    Material ivory(0.4, 0.4, 0.3);
    Material red_rubber(0.3, 0.1, 0.1);
    // define a sphere
    Eigen::Vector3f center(0, 0, 10);
    float radius(1);
    Sphere sphere(center, radius);

    render(sphere); 
    return 0;
}
