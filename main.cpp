#include <iostream>
#include "vec3.h"
#include "color.h"

int main() {
    //ppm file output
    //use ppm image viewer software or extension
    //image
    int img_width = 256;
    int img_height = 256;

    //render
    std::cout << "P3\n" << img_width << ' ' << img_height << "\n255\n";

    for (int j = 0; j < img_height; j++) {
        std::clog << "\rScanlines remaining: " << (img_height - j) << ' ' << std::flush;
        for (int i = 0; i < img_width; i++) {
            auto pixel_color = color(double(i)/(img_width - 1), double(j)/(img_height - 1), 0);
            write_color(std::cout, pixel_color);
        }
    }

    //spaces needed in order to overwrit the "scalines remaining" update from code running
    std::clog << "\rDone.                    \n";
    return 0;
}