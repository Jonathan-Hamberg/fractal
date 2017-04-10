#include <complex>
#include <iostream>

#include <glm/glm.hpp>

#include "view.h"
#include "mandlebrot.h"

void render_mandlebrot(std::vector<uint8_t> &data, int width, int height, view region, int iterations)
{
	// Calculate the dx and ty steps.
	double dx = region.GetWidth() / width;
	double dy = region.GetHeight() / height;
	double Cr, Ci, Zr, Zi, Zrt;

	uint8_t *data_pointer = data.data();

	// Iteratively calculatet he steps for each pixel.
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			int i;
			Cr = region.GetX() + x*dx;
			Ci = region.GetY() + y*dy;
			Zr = Cr;
			Zi = Ci;

			// Find the number of steps to divergence.
			for (i = 0; i < iterations && Zr * Zr + Zi * Zi < 4; i++)
			{
				Zrt = Zr; // Keep tempporary value of Zr.
				Zr = Zr * Zr - Zi * Zi + Cr;
				Zi = 2 * Zrt * Zi + Ci;
			}

			// Assign the steps to the data vector.
			data_pointer[y * width + x] = i;
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

	int N = iterations;
	int N3 = N * N * N;
	int n, b, nn, r, g;
	double t;
	uint8_t     *steps_data = steps.data();
	glm::u8vec3 *color_data = colors.data();

	for (unsigned i = 0; i < steps.size(); i++)
	{
		n = steps_data[i];
		t = (double)n / iterations;
		b = n / (N*N);
		nn = n - b*N*N;
		r = nn / N;
		g = nn - r * N;

		color_data[i].r = r;
		color_data[i].g = g;
		color_data[i].b = b;
	}
}


