#include "stdafx.h"
#include "getColor.h"

getColor::~getColor()
{
}

COLORREF getColor::getColorForPixel(double color) {
	COLORREF new_color;
	double t = 0.5*(color + 1);
	new_color = RGB(255*t, 255*(1-t), 0);

	return new_color;
}