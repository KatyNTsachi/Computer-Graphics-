#pragma once
class getColor
{
public:

	//default functions 
	getColor() {};
	~getColor();
	
	//functions
	COLORREF getColorForPixel(double func_val);

	//vars
	int color_type;
	COLORREF color1;
	COLORREF color2;

};

