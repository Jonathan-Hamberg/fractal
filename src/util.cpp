#include "util.h"

glm::mat4 linear_transform(float x1, float x2, float y1, float y2,
	float x3, float x4, float y3, float y4)
{
	glm::mat4 transform;

	// Calculate the horizontal ratio.
	float h_ratio = (x4 - x3) / (x2 - x1);

	// Calculate the verticle ratio.
	float v_ratio = (y4 - y3) / (y2 - y1);

	// Assign the x scale value.
	transform[0][0] = h_ratio;

	// Assign the y scale value.
	transform[1][1] = v_ratio;

	// Assign the x translate value.
	transform[3][0] = -x1 * h_ratio + x3;

	// Assign the y translate value.
	transform[3][1] = -y1 * v_ratio + y3;

	// Return the transform matrix.
	return transform;
}