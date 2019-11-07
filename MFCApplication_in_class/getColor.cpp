#include "stdafx.h"
#include "getColor.h"

getColor::~getColor()
{
}

COLORREF getColor::getColorForPixel(double func_val) {
	COLORREF new_color;
	double t;
	
	if (color_type == 1) {

		t = 0.5*(func_val + 1);
		new_color = color1 * func_val + color2 * func_val;
		
	}
	else {
		new_color = func_val > 0 ? color1 : color2;
	}

	return new_color;
}