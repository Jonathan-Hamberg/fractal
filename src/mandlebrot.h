#pragma once

#include <cstdint>
#include <vector>

void render_mandlebrot(std::vector<uint8_t> &data, int width, int height, float x1, float y1, float x2, float y2, int iterations);
void color_mandlebrot(std::vector<uint8_t> &steps, std::vector<glm::u8vec3> &colors, int iterations);