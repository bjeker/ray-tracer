#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <iostream>

//placing a sphere for ray tracing
bool hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = center - r.origin();

    //equation for quadratic positioning broken down
    auto a = dot(r.direction(), r.direction());
    auto b = -2.0 * dot(r.direction(), oc);
    auto c = dot(oc, oc) - radius * radius;
    //quadratic formula
    auto discremenant = b * b - 4 * a * c;

    return (discremenant >= 0);
}

//colors the ray when hit
color ray_color(const ray& r) {
    //check if ray hits sphere placed at -1
    if (hit_sphere(point3(0, 0, -1), 0.5, r)) {
        return color(1, 0, 0);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);

    return (1.0 - a) * color(1.0, 1.0, 1.0) + color(0.5, 0.7, 1.0);
}

int main() {
    //ppm file output
    //use ppm image viewer software or extension
    //image
    auto aspect_ratio = 16.0 / 9.0;
    int img_width = 400;

    //calc img height, ensure > 1
    int img_height = int(img_width / aspect_ratio);
    img_height = (img_height < 1) ? 1 : img_height;

    //camera
    //length from cam center to viewport
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    //get the actual ratio for image, not just ideal from aspect ratio
    auto viewport_width = viewport_height * (double(img_width) / img_height);
    auto camera_center = point3(0, 0, 0);

    //calc vectors across horizontal and down vertical viewport edges
    //account for flipped vertical
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    //calc horizontal and vertical delta vectors from pixel to pixel
    auto pixel_delta_u = viewport_u / img_width;
    auto pixel_delta_v = viewport_v / img_height;

    //calc location of upper left pixel
    auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    //render
    std::cout << "P3\n" << img_width << ' ' << img_height << "\n255\n";

    for (int j = 0; j < img_height; j++) {
        std::clog << "\rScanlines remaining: " << (img_height - j) << ' ' << std::flush;
        for (int i = 0; i < img_width; i++) {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    //spaces needed in order to overwrit the "scalines remaining" update from code running
    std::clog << "\rDone.                    \n";

    return 0;
}