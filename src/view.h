#pragma once

#include "glm/glm.hpp"

class view
{
public:
	view();
	view(double x1, double y1, double w, double h);
	
	void Zoom(double scale);
	void Translate(double x, double y);
	void SetCenter(double x, double y);

	double GetX();
	double GetY();
	double GetWidth();
	double GetHeight();

	void SetWidth(double width);
	void SetHeight(double height);
	
private:
	glm::dvec4 region;
};