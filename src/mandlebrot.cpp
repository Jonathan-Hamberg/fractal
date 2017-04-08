#include <complex>
#include <iostream>

#include <glm/glm.hpp>

#include "mandlebrot.h"

void render_mandlebrot(std::vector<uint8_t> &data, int width, int height, float x1, float y1, float x2, float y2, int iterations)
{
	// Calculate the dx and ty steps.
	float dx = (x2 - x1) / width;
	float dy = (y2 - y1) / height;

	// Iteratively calculatet he steps for each pixel.
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			int i;
			std::complex<float> C(x1 + x*dx, y1 + y*dy);
			std::complex<float> Z = C;
			float magnitude = Z.real() * Z.real() + Z.imag() * Z.imag();

			// Find the number of steps to divergence.
			for (i = 0; i < iterations && magnitude < 4; i++)
			{
				Z = Z*Z + C;
				magnitude = Z.real() * Z.real() + Z.imag() * Z.imag();
			}

			// Assign the steps to the data vector.
			data[y * width + x] = i;
		}
	}
}

void color_mandlebrot(std::vector<uint8_t> &steps, std::vector<glm::u8vec3> &colors, int iterations)
{
	if (steps.size() != colors.size())
	{
		std::cout << "ERROR:MANDLEBROT:STEPS-COLORS_SIZE_MISMATCH\n" << steps.size() << " != " << colors.size() << std::endl;
		return;
	}

	for (unsigned i = 0; i < steps.size(); i++)
	{
		uint8_t step_count = steps[i] / iterations * 255;
		colors[i] = glm::u8vec3(step_count, step_count, step_count);
	}
}


