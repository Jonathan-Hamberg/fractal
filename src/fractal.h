#pragma once

#include <functional>
#include <vector>

#include "glm/glm.hpp"

#include "view.h"

void render_full(std::function<uint32_t(double, double, uint32_t)> func_render,
	uint32_t *render_data,
	glm::u16vec2 render_size,
	glm::dvec4 region,
	uint32_t iterations);

void render_full_block(std::function<uint32_t(double, double, uint32_t)> func_render,
	uint32_t *render_data,
	glm::u16vec4 render_size,
	uint32_t pitch,
	glm::dvec4 region,
	uint32_t iterations);