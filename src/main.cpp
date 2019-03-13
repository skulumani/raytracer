#include "renderer.hpp"
#include "geometry.hpp"

int main() {

    Vec<2, int> vector(1, 2);
    
    Vec3f center(0, 0, 10);
    float radius(1);
    Sphere sphere(center, radius);
    render(sphere); 
    return 0;
}
