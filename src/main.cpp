#include "renderer.hpp"
#include "geometry.hpp"
#include "camera.hpp"

int main() {
    // define a camera
    Camera cam;
    cam.image_size(500, 500);

    // define different materials
    Material ivory((Eigen::Vector3f() << 0.6, 0.3, 0).finished(),
            (Eigen::Vector3f() << 0.4, 0.4, 0.3).finished(),
            50);
    Material red_rubber((Eigen::Vector3f() << 0.9, 0.1, 0).finished(),
            (Eigen::Vector3f() << 0.3, 0.1, 0.1).finished(),
            20);
    Material plywood((Eigen::Vector3f() << 0.9, 0.1, 0).finished(),
            (Eigen::Vector3f() << 0.835, 0.796, 0.325).finished(),
            5);
    Material teal((Eigen::Vector3f() << 0.8, 0.2, 0).finished(), 
            (Eigen::Vector3f() << 0.325, 0.835, 0.796).finished(),
            20);
    Material mirror((Eigen::Vector3f() << 0, 10, 0.8).finished(),
            (Eigen::Vector3f() << 1, 1, 1).finished(),
            1425);

    // define a sphere
    // positions are in the camera frame
    Eigen::Vector3f center(1, 1, 2);
    float radius(1);
    Sphere sphere(center, radius);

    std::vector<Sphere> spheres;
    spheres.push_back(Sphere(-3,    0,   16, 2,      ivory));
    spheres.push_back(Sphere(-1.0, -1.5, 12, 2, red_rubber));
    spheres.push_back(Sphere( 1.5, -0.5, 18, 3, plywood));
    spheres.push_back(Sphere( 7,    5,   18, 4,      teal));

    // lights   
    std::vector<Light> lights;
    lights.push_back(Light((Eigen::Vector3f() << 20, -20, 15).finished(), 0.7));
    lights.push_back(Light((Eigen::Vector3f() << -30, -50,  25).finished(), 1.0));
    lights.push_back(Light((Eigen::Vector3f() << -2, -5,  -1).finished(), 0.7));
    
    /* render(sphere); */
    /* render(cam, sphere); */

    /* render(spheres); */
    /* render(cam, spheres); */

    /* render(spheres, lights); */ 
    /* render(cam, spheres, lights); */

    phong_render(cam, spheres, lights);

    return 0;
}
