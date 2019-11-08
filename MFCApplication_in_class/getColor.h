#pragma once
class getColor
{
public:

	//default functions 
	getColor() {};
	getColor(COLORREF color1_, COLORREF color2_, int colorMode_);
	~getColor();
	
	//functions
	COLORREF getColorForPixel(double func_val);

	//vars
	int color_type;
	COLORREF color1;
	COLORREF color2;

};

