#include "stdafx.h"
#include "getColor.h"

getColor::~getColor()
{
}

getColor::getColor(COLORREF color1_, COLORREF color2_, int colorMode_)
{
	color1 = color1_;
	color2 = color2_;
	color_type = colorMode_;
}

COLORREF getColor::getColorForPixel(double func_val) {
	COLORREF new_color;
	double t;
	
	if (color_type == 1) {

		t = 0.5*(func_val + 1);
		new_color = color1 * (1-t) + color2 * t;
		
	}
	else {
		new_color = func_val > 0 ? color1 : color2;
	}

	return new_color;
}