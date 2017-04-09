#include "view.h"

View::View()
{
	_x1 = 0.0f;
	_y1 = 0.0f;
	_x2 = 0.0f;
	_y2 = 0.0f;
}

View::View(float x1, float y1, float x2, float y2)
{
	_x1 = x1;
	_y1 = y1;
	_x2 = x2;
	_y2 = y2;
	
}

void View::Zoom(float scale)
{
	float centerX = (_x2 + _x1) / 2;;
	float centerY = (_y2 + _y1) / 2;
	float width = _x2 - _x1;
	float height = _y2 - _y1;

	_x1 = centerX - width / 2 / scale;
	_y1 = centerY + height / 2 / scale;
	_x2 = centerX + width / 2 / scale;
	_y2 = centerY - height / 2 / scale;
}

void View::Translate(float x, float y)
{
	_x1 += x;
	_y1 -= y;
	_x2 += x;
	_y2 -= y;
}

void View::SetCenter(float x, float y)
{
	float width = _x2 - _x1;
	float height = _y2 - _y1;

	_x1 = x - width / 2;
	_y1 = y + height / 2;
	_x2 = x + width / 2;
	_y2 = y - height / 2;
}

float View::GetX()
{
	return _x1;
}

float View::GetY()
{
	return _y1;
}

float View::GetWidth()
{
	return _x2 - _x1;
}

float View::GetHeight()
{
	return _y2 - _y1;
}

float View::GetX1()
{
	return _x1;
}

float View::GetY1()
{
	return _y1;
}

float View::GetX2()
{
	return _x2;
}

float View::GetY2()
{
	return _y2;
}

float View::GetCenterX()
{
	return _x1 + (_x2 - _x1) / 2;
}

float View::GetCenterY()
{
	return _y1 + (_y2 - _y1) / 2;
}
