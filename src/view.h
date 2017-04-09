#pragma once

class View
{
public:
	View();
	View(float x1, float y1, float x2, float y2);
	
	void Zoom(float scale);
	void Translate(float x, float y);

	void SetCenter(float x, float y);

	float GetX();
	float GetY();
	float GetWidth();
	float GetHeight();

	float GetX1();
	float GetY1();
	float GetX2();
	float GetY2();
	
	float GetCenterX();
	float GetCenterY();
private:
	float _x1, _y1, _x2, _y2;
};