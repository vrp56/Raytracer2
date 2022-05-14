#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "triangle.h"
#include "OBJ_Loader.h"
#include <iostream>

void loadMesh(hittable_list world)
{
    objl::Loader Loader;
    bool loadout = Loader.LoadFile("box_stack.obj");

    if (loadout)
    {
        // go through each loaded mesh 
        for (int i = 0; i < Loader.LoadedMeshes.size(); i++)
        {
            objl::Mesh curMesh = Loader.LoadedMeshes[i];

            // loop through mesh and add each triangle to the world 
            

            for (int j = 0; j < curMesh.Vertices.size(); j++)
            {
                point3 p0(
                    curMesh.Vertices[j].Position.X,
                    curMesh.Vertices[j].Position.Y,
                    curMesh.Vertices[j].Position.Z
                );
                std::cerr << "Vertex " << j << ": ";
                std::cerr << p0 << std::endl;
            }
        }
    }
    else std::cerr << "File failed to load";
}

color ray_color(const ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1, 1, 1));
        //return rec.u * color(1.0, 0, 0) + rec.v * color(0, 1.0, 0) + (1 - rec.u - rec.v) * color(0, 0, 1.0);
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() {
	// Image 
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;

    // World
    hittable_list world;
    loadMesh(world);
    //world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    //world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));
    //world.add(make_shared<triangle>(point3(-1, -1, -.8), point3(1, -1, -1), point3(0, 1, -1)));

    // Camera
    camera cam;

	// Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j) {
        //std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random_double()) / (image_width - 1);
                auto v = (j + random_double()) / (image_height - 1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world);
            }
            //write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }

    std::cerr << "\nDone.\n";
}