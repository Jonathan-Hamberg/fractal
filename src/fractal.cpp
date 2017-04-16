#include "fractal.h"

#include <thread>
#include <iostream>

void render_full(std::function<uint32_t(double, double, uint32_t)> func_render,
	uint32_t *render_data,
	glm::u16vec2 render_size,
	glm::dvec4 region,
	uint32_t iterations)
{
	uint32_t x_index = render_size.x / 2;
	uint32_t y_index = render_size.y / 2;

	double deltaX = (double)region[2] / render_size.x;
	double deltaY = (double)region[3] / render_size.y;

	double x1_pos = region[0] + x_index * deltaX;
	double y1_pos = region[1] + y_index * deltaY;
	double x2_pos = x1_pos + deltaX;
	double y2_pos = y1_pos + deltaY;
	double x_end = region[0] + region[2];
	double y_end = region[1] + region[3];

	// Bottom left region.
	std::thread thread1(render_full_block,
		func_render,
		render_data,
		glm::u16vec4( 0, 0, x_index, y_index ),
		render_size.x,
		glm::vec4( region[0], region[1], x1_pos - region[0], y1_pos - region[1]),
		iterations);

	// Bottom right region.
	std::thread thread2(render_full_block,
		func_render,
		render_data,
		glm::u16vec4(x_index + 1, 0, render_size.x - 1, y_index),
		render_size.x,
		glm::vec4(x2_pos, region[1], x_end - x2_pos, y1_pos - region[1]),
		iterations);

	// Top left region.
	std::thread thread3(render_full_block,
		func_render,
		render_data,
		glm::u16vec4(0, y_index + 1, x_index, render_size.y - 1),
		render_size.x,
		glm::vec4(region[0], y2_pos, x1_pos - region[0], y_end - y2_pos),
		iterations);

	// Top right region.
	std::thread thread4(render_full_block,
		func_render,
		render_data,
		glm::u16vec4(x_index + 1, y_index + 1, render_size.x - 1, render_size.y - 1),
		render_size.x,
		glm::vec4(x2_pos, y2_pos, x_end - x2_pos, y_end - y2_pos),
		iterations);

	std::cout << y1_pos - region[1] << " " << y1_pos - region[1] << " " << y_end - y2_pos << " " << y_end - y2_pos << std::endl;

	thread1.join();
	thread2.join();
	thread3.join();
	thread4.join();
}

void render_full_block(std::function<uint32_t(double Re, double Im, uint32_t iterations)> func_render,
	uint32_t *render_data,
	glm::u16vec4 render_size,
	uint32_t pitch,
	glm::dvec4 region,
	uint32_t iterations)
{
	uint32_t x_origin = render_size[0];
	uint32_t y_origin = render_size[1];

	uint32_t num_x = render_size[2] - render_size[0];
	uint32_t num_y = render_size[3] - render_size[1];

	double Re, Im, deltaR, deltaI;

	deltaR = region[2] / ( render_size[2] - render_size[0] );
	deltaI = region[3] / ( render_size[3] - render_size[1] );

	for (uint32_t x = 0; x <= num_x; x++)
	{
		for (uint32_t y = 0; y <= num_y; y++)
		{
			Re = region[0] + x * deltaR;
			Im = region[1] + y * deltaI;

			render_data[pitch * (y_origin + y) + x_origin + x] = func_render(Re, Im, iterations);
		}
	}
}
