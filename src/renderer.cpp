#include <cstdint>
#include <algorithm>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "renderer.hpp"
#include "geometry.hpp"

void render(const Sphere& sphere) {
    // size of image
    const int width    = 64;
    const int height   = 64;

    // define camera FOV
    const float fov_h = M_PI/3.0;
    const float fov_w = M_PI/3.0;
    
    // this defines the camera frame (and images on the image plane)
    // TODO Rotate these vectors camera to inertial frame
    const Eigen::Vector3f view_axis(0, 0, 1);
    const Eigen::Vector3f up_axis(0, 1, 0);
    const Eigen::Vector3f right_axis(1, 0, 0);

    const float dist(height / (2.0 * std::tan(fov_h/2.0)));
    const Eigen::Vector3f cam_axis(0, 0, dist);

    // data for the image RGB 
    std::vector<Eigen::Vector3f, Eigen::aligned_allocator<Eigen::Vector3f> > framebuffer(width*height);
    Eigen::Vector3f origin(0, 0, 0); 
    #pragma omp parallel for
    for (size_t jj = 0; jj < height; jj++) {
        for (size_t ii = 0; ii < width; ii++) {

            // define view direction
            Eigen::Vector3f ray_vec = cam_axis + ((ii+0.5) - width/2) * right_axis + ((jj+0.5) - height/2) * up_axis;

            /* framebuffer[ii+jj*width] = (Eigen::Vector3f() << jj/float(height),ii/float(width), 0).finished(); */
            framebuffer[ii+jj*width] = cast_ray(origin, ray_vec.normalized(), sphere);

        }
    }
   


    // save to file (need to loop through framebuffer and convert it to another 
    // data array type for STB

    std::uint8_t image[width * height * 3];

    #pragma omp parallel for
    for (size_t ii = 0; ii < width * height; ii++) {
        image[ii * 3 + 0] = (int)(255 * framebuffer[ii]( 0 ));
        image[ii * 3 + 1] = (int)(255 * framebuffer[ii]( 1 ));
        image[ii * 3 + 2] = (int)(255 * framebuffer[ii]( 2 ));
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

void render(const std::vector<Sphere>& spheres) {

    // size of image
    const int width    = 640;
    const int height   = 480;

    // define camera FOV
    const float fov_h = M_PI/3.0;
    const float fov_w = M_PI/3.0;
    
    // this defines the camera frame (and images on the image plane)
    // TODO Rotate these vectors camera to inertial frame
    const Eigen::Vector3f view_axis(0, 0, 1);
    const Eigen::Vector3f up_axis(0, 1, 0);
    const Eigen::Vector3f right_axis(1, 0, 0);

    const float dist(height / (2.0 * std::tan(fov_h/2.0)));
    const Eigen::Vector3f cam_axis(0, 0, dist);

    // data for the image RGB 
    std::vector<Eigen::Vector3f, Eigen::aligned_allocator<Eigen::Vector3f> > framebuffer(width*height);
    Eigen::Vector3f origin(0, 0, 0); 
    #pragma omp parallel for
    for (size_t jj = 0; jj < height; jj++) {
        for (size_t ii = 0; ii < width; ii++) {

            // define view direction
            Eigen::Vector3f ray_vec = cam_axis + ((ii+0.5) - width/2) * right_axis + ((jj+0.5) - height/2) * up_axis;

            framebuffer[ii+jj*width] = cast_ray(origin, ray_vec.normalized(), spheres);

        }
    }
   


    // save to file (need to loop through framebuffer and convert it to another 
    // data array type for STB
    std::uint8_t image[width * height * 3];

    #pragma omp parallel for
    for (size_t ii = 0; ii < width * height; ii++) {
        image[ii * 3 + 0] = (int)(255 * framebuffer[ii]( 0 ));
        image[ii * 3 + 1] = (int)(255 * framebuffer[ii]( 1 ));
        image[ii * 3 + 2] = (int)(255 * framebuffer[ii]( 2 ));
    }

    stbi_write_jpg("out.jpg",width, height, 3, image, 95);

}

void render(const std::vector<Sphere>& spheres, 
        const std::vector<Light>& lights) {

    // size of image
    const int width    = 640;
    const int height   = 480;

    // define camera FOV
    const float fov_h = M_PI/3.0;
    const float fov_w = M_PI/3.0;
    
    // this defines the camera frame (and images on the image plane)
    // TODO Rotate these vectors camera to inertial frame
    const Eigen::Vector3f view_axis(0, 0, 1);
    const Eigen::Vector3f up_axis(0, 1, 0);
    const Eigen::Vector3f right_axis(1, 0, 0);

    const float dist(height / (2.0 * std::tan(fov_h/2.0)));
    const Eigen::Vector3f cam_axis(0, 0, dist);

    // data for the image RGB 
    std::vector<Eigen::Vector3f, Eigen::aligned_allocator<Eigen::Vector3f> > framebuffer(width*height);
    Eigen::Vector3f origin(0, 0, 0); 
    #pragma omp parallel for
    for (size_t jj = 0; jj < height; jj++) {
        for (size_t ii = 0; ii < width; ii++) {

            // define view direction
            Eigen::Vector3f ray_vec = cam_axis + ((ii+0.5) - width/2) * right_axis + ((jj+0.5) - height/2) * up_axis;

            framebuffer[ii+jj*width] = cast_ray(origin, ray_vec.normalized(), spheres, lights);

        }
    }
   


    // save to file (need to loop through framebuffer and convert it to another 
    // data array type for STB
    std::uint8_t image[width * height * 3];

    #pragma omp parallel for
    for (size_t ii = 0; ii < width * height; ii++) {
        image[ii * 3 + 0] = (int)(255 * std::max(0.0f, std::min(1.0f, (float)(framebuffer[ii]( 0 )))));
        image[ii * 3 + 1] = (int)(255 * std::max(0.0f, std::min(1.0f, (float)(framebuffer[ii]( 1 )))));
        image[ii * 3 + 2] = (int)(255 * std::max(0.0f, std::min(1.0f, (float)(framebuffer[ii]( 2 )))));
    }

    stbi_write_jpg("out.jpg",width, height, 3, image, 95);


}

void phong_render(const std::vector<Sphere>& spheres, 
        const std::vector<Light>& lights) {

    // size of image
    const int width    = 640;
    const int height   = 480;

    // define camera FOV
    const float fov_h = M_PI/3.0;
    const float fov_w = M_PI/3.0;
    
    // this defines the camera frame (and images on the image plane)
    // TODO Rotate these vectors camera to inertial frame
    const Eigen::Vector3f view_axis(0, 0, 1);
    const Eigen::Vector3f up_axis(0, 1, 0);
    const Eigen::Vector3f right_axis(1, 0, 0);

    const float dist(height / (2.0 * std::tan(fov_h/2.0)));
    const Eigen::Vector3f cam_axis(0, 0, dist);

    // data for the image RGB 
    std::vector<Eigen::Vector3f, Eigen::aligned_allocator<Eigen::Vector3f> > framebuffer(width*height);
    Eigen::Vector3f origin(0, 0, 0); 
    #pragma omp parallel for
    for (size_t jj = 0; jj < height; jj++) {
        for (size_t ii = 0; ii < width; ii++) {

            // define view direction
            Eigen::Vector3f ray_vec = cam_axis + ((ii+0.5) - width/2) * right_axis + ((jj+0.5) - height/2) * up_axis;

            framebuffer[ii+jj*width] = cast_ray(origin, ray_vec.normalized(), spheres, lights);

        }
    }
   


    // save to file (need to loop through framebuffer and convert it to another 
    // data array type for STB
    std::uint8_t image[width * height * 3];

    #pragma omp parallel for
    for (size_t ii = 0; ii < width * height; ii++) {
        image[ii * 3 + 0] = (int)(255 * std::max(0.0f, std::min(1.0f, (float)(framebuffer[ii]( 0 )))));
        image[ii * 3 + 1] = (int)(255 * std::max(0.0f, std::min(1.0f, (float)(framebuffer[ii]( 1 )))));
        image[ii * 3 + 2] = (int)(255 * std::max(0.0f, std::min(1.0f, (float)(framebuffer[ii]( 2 )))));
    }

    stbi_write_jpg("out.jpg",width, height, 3, image, 95);


}
