#include <cstdint>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "renderer.hpp"
#include "geometry.hpp"

void render(const Sphere& sphere) {
    // size of image
    const int width    = 800;
    const int height   = 800;

    // define camera FOV
    const float fov_h = M_PI/3.0;
    const float fov_w = M_PI/3.0;
    
    // this defines the camera frame (and images on the image plane)
    // TODO Rotate these vectors camera to inertial frame
    const Vec3f view_axis(0, 0, 1);
    const Vec3f up_axis(0, 1, 0);
    const Vec3f right_axis(1, 0, 0);

    const float dist(10);
    const Vec3f cam_axis(0, 0, dist);

    // data for the image RGB 
    std::vector<Vec3f> framebuffer(width*height);
    
    #pragma omp parallel for
    for (size_t jj = 0; jj < height; jj++) {
        for (size_t ii = 0; ii < width; ii++) {

            // define view direction
            /* Vec3f ray_vec = cam_axis + ((ii+0.5) - width/2) * right_axis + ((jj+0.5) - height/2) * up_axis; */

            float dir_x = (ii + 0.5) - width/2;
            float dir_y = (jj + 0.5) - height/2;
            float dir_z = height/(2.0*std::tan(fov_h/2));
            Vec3f ray_vec(dir_x, dir_y, dir_z);

            /* framebuffer[ii+jj*width] = Vec3f(jj/float(height),ii/float(width), 0); */
            framebuffer[ii+jj*width] = cast_ray(Vec3f(0, 0, 0), ray_vec.normalize(), sphere);

        }
    }
   


    // save to file (need to loop through framebuffer and convert it to another 
    // data array type for STB

    std::uint8_t image[width * height * 3];

    #pragma omp parallel for
    for (size_t ii = 0; ii < width * height; ii++) {
        image[ii * 3 + 0] = (int)(255 * framebuffer[ii][0]);
        image[ii * 3 + 1] = (int)(255 * framebuffer[ii][1]);
        image[ii * 3 + 2] = (int)(255 * framebuffer[ii][2]);
    }

    stbi_write_jpg("out.jpg",width, height, 3, image, 95);

    /* std::ofstream ofs; // save the framebuffer to file */
    /* ofs.open("./out.ppm"); */
    /* ofs << "P6\n" << width << " " << height << "\n255\n"; */
    /* for (size_t i = 0; i < height*width; ++i) { */
    /*     for (size_t j = 0; j<3; j++) { */
    /*         ofs << (char)(255 * std::max(0.f, std::min(1.f, framebuffer[i][j]))); */
    /*     } */
    /* } */
    /* ofs.close(); */
}
