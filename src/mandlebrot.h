#pragma once

#include <cstdint>
#include <vector>

#include "view.h"

void render_mandlebrot(std::vector<uint8_t> &data, int width, int height, View region, int iterations);
void color_mandlebrot(std::vector<uint8_t> &steps, std::vector<glm::u8vec3> &colors, int iterations);