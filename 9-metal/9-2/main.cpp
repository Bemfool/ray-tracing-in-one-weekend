#include <iostream>
#include <fstream>
#include <cfloat>
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "random.h"
#include "metal.h"
#include "lambertian.h"
using namespace std;

int nx = 200;	// screen width
int ny = 100;	// screen height
int ns = 100;	// sample number

camera cam;		// camera

vec3 color(const ray& r, hittable *world, int depth) {
	hit_record rec;		// store the closest hit point
	if (world->hit(r, 0.001, FLT_MAX, rec)) {
		ray scattered;
		vec3 attenuation;
		if (depth < 50 && (rec.mat_ptr)->scatter(r, rec, attenuation, scattered)) {
			return attenuation * color(scattered, world, depth + 1);
		}
		else {
			return vec3(0, 0, 0);
		}
	}
	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5 * (unit_direction.y() + 1.0);
	// blendedValue = (1 - t) * startValue + t * endValue;
	return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main()
{
	std::ofstream out;
	out.open("result.ppm", std::ios::out | std::ios::binary | std::ios::trunc);
	if (!out.is_open()) {
		std::cout << "Result.ppm creation failed." << std::endl;
		return -1;
	}

	out << "P3\n" << nx << " " << ny << "\n255\n";
	
	hittable *list[4];
	list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.8, 0.3, 0.3)));
	list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
	list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.3));
	list[3] = new sphere(vec3(-1, 0, -1), 0.5, new metal(vec3(0.8, 0.8, 0.8), 1));
	hittable *world = new hittable_list(list, 4);
	
	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			vec3 col(0, 0, 0);
			for (int s = 0; s < ns; s++) {
				float u = float(i + random_double()) / float(nx);
				float v = float(j + random_double()) / float(ny);
				ray r = cam.get_ray(u, v);
				col += color(r, world,  0);
			}
			col /= float(ns);
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int ir = int(255.99 * col.r());
			int ig = int(255.99 * col.g());
			int ib = int(255.99 * col.b());
			out << ir << " " << ig << " " << ib << "\n";
		}
	}
	out.close();
	std::cout << "Image creation succeeded." << std::endl;
	system("pause");
    return 0;
}
