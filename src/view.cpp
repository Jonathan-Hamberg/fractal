#include "view.h"

view::view() : region(-2.0, -2.0, 4.0, 4.0)
{
}

view::view(double x, double y, double w, double h) :
	region(x, y, w, h)
{
}

void view::Zoom(double scale)
{
	region[0] += region[2] * (1 - 1 / scale) / 2.0;
	region[1] += region[3] * (1 - 1 / scale) / 2.0;
	region[2] /= scale;
	region[3] /= scale;
}

void view::Translate(double x, double y)
{
	region[0] += x;
	region[1] += y;
}

void view::SetCenter(double x, double y)
{
	region[0] = x - region[2] / 2;
	region[1] = y - region[3] / 2;
}
double view::GetX()
{
	return region[0];
}
double view::GetY()
{
	return region[1];
}
double view::GetWidth()
{
	return region[2];
}
double view::GetHeight()
{
	return region[3];
}

void view::SetWidth(double width)
{
	region[0] += (region[2] - width) / 2;
	region[2] = width;
}

void view::SetHeight(double height)
{
	region[1] += (region[3] - height) / 2;
	region[3] = height;
}
