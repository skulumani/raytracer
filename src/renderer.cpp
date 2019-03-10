#include "renderer.hpp"
#include "geometry.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


void render( void ) {
    // size of image
    const int width    = 1024;
    const int height   = 768;
    
    // data for the image 
    std::vector<Vec3f> framebuffer(width*height);

    for (size_t jj = 0; jj < height; jj++) {
        for (size_t ii = 0; ii < width; ii++) {
            framebuffer[ii+jj*width] = Vec3f(jj/float(height),ii/float(width), 0);
        }
    }
    
    // save to file (need to loop through framebuffer and convert it to another 
    // data array type for STB
    /* stbi_write_jpg("output.jpg", width, height, 3, framebuffer, 95); */
    std::ofstream ofs; // save the framebuffer to file
    ofs.open("./out.ppm");
    ofs << "P6\n" << width << " " << height << "\n255\n";
    for (size_t i = 0; i < height*width; ++i) {
        for (size_t j = 0; j<3; j++) {
            ofs << (char)(255 * std::max(0.f, std::min(1.f, framebuffer[i][j])));
        }
    }
    ofs.close();
}
