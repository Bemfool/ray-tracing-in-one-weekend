#include <iostream>
#include <fstream>

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
			float r = float(i) / float(nx);
			float g = float(j) / float(ny);
			float b = 0.2;
			int ir = int(255.99 * r);
			int ig = int(255.99 * g);
			int ib = int(255.99 * b);
			out << ir << " " << ig << " " << ib << "\n";
		}
	}
	out.close();
	std::cout << "Image creation succeeded." << std::endl;
	system("pause");
    return 0;
}

