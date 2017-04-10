#include "view.h"

view::view()
{
	_x1 = 0.0f;
	_y1 = 0.0f;
	_x2 = 0.0f;
	_y2 = 0.0f;
}

view::view(double x1, double y1, double x2, double y2)
{
	_x1 = x1;
	_y1 = y1;
	_x2 = x2;
	_y2 = y2;
	
}

void view::Zoom(double scale)
{
	double centerX = (_x2 + _x1) / 2;;
	double centerY = (_y2 + _y1) / 2;
	double width = _x2 - _x1;
	double height = _y2 - _y1;

	_x1 = centerX - width / 2 / scale;
	_y1 = centerY + height / 2 / scale;
	_x2 = centerX + width / 2 / scale;
	_y2 = centerY - height / 2 / scale;
}

void view::Translate(double x, double y)
{
	_x1 += x;
	_y1 -= y;
	_x2 += x;
	_y2 -= y;
}

void view::SetCenter(double x, double y)
{
	double width = _x2 - _x1;
	double height = _y2 - _y1;

	_x1 = x - width / 2;
	_y1 = y + height / 2;
	_x2 = x + width / 2;
	_y2 = y - height / 2;
}

double view::GetX()
{
	return _x1;
}

double view::GetY()
{
	return _y1;
}

double view::GetWidth()
{
	return _x2 - _x1;
}

double view::GetHeight()
{
	return _y2 - _y1;
}

double view::GetX1()
{
	return _x1;
}

double view::GetY1()
{
	return _y1;
}

double view::GetX2()
{
	return _x2;
}

double view::GetY2()
{
	return _y2;
}

double view::GetCenterX()
{
	return _x1 + (_x2 - _x1) / 2;
}

double view::GetCenterY()
{
	return _y1 + (_y2 - _y1) / 2;
}
