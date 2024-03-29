#include <iostream>
#include <fstream>
#include "vec3.h"

int nx = 200;
int ny = 100;

int main()
{
	std::ofstream out;
	out.open("result.ppm", std::ios::out | std::ios::binary | std::ios::trunc);
	if (!out.is_open()) {
		std::cout << "Result.ppm creation failed." << std::endl;
		return -1;
	}

	out << "P3\n" << nx << " " << ny << "\n255\n";
	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			vec3 col(float(i) / float(nx), float(j) / float(ny), 0.2);
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

