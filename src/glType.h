#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

struct VertexPos2Tex2
{
	glm::vec2 pos;
	glm::vec2 uv;

	VertexPos2Tex2(float x, float y, float u, float v) : pos(x, y), uv(u, v)
	{

	}

	static void VertexAttrib()
	{
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPos2Tex2), (GLvoid*)(0));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPos2Tex2), (GLvoid*)(sizeof(glm::vec2)));
		glEnableVertexAttribArray(1);
	}
};