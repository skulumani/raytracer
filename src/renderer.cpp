#include <cstdint>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "renderer.hpp"
#include "geometry.hpp"

void render( void ) {
    // size of image
    const int width    = 1024;
    const int height   = 768;
    
    // data for the image RGB 
    std::vector<Vec3f> framebuffer(width*height);

    for (size_t jj = 0; jj < height; jj++) {
        for (size_t ii = 0; ii < width; ii++) {
            framebuffer[ii+jj*width] = Vec3f(jj/float(height),ii/float(width), 0);
        }
    }
    
    // save to file (need to loop through framebuffer and convert it to another 
    // data array type for STB
    std::uint8_t image[width * height * 3];
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
