#pragma once

#include <glm/glm.hpp>

class Texture
{
public:
	Texture();
	Texture(int width, int height, glm::u8vec3 *data);
	~Texture();

	GLint ID();
	int Width();
	int Height();
	void UpdateData(glm::u8vec3 *data, int width, int height);
private:
	unsigned _texture;
	int _width;
	int _height;
};