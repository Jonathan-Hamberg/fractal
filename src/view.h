#pragma once

class view
{
public:
	view();
	view(double x1, double y1, double x2, double y2);
	
	void Zoom(double scale);
	void Translate(double x, double y);

	void SetCenter(double x, double y);

	double GetX();
	double GetY();
	double GetWidth();
	double GetHeight();

	double GetX1();
	double GetY1();
	double GetX2();
	double GetY2();
	
	double GetCenterX();
	double GetCenterY();
private:
	double _x1, _y1, _x2, _y2;
};