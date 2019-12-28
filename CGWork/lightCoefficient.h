#pragma once
#include "stdafx.h"

class LightCoefficient
{
public:
	LightCoefficient();
	LightCoefficient::LightCoefficient(double x, double y, double z);
	~LightCoefficient();
	LightCoefficient operator * (LightCoefficient const &lightCoefficient2);
	LightCoefficient operator * (double a);
	LightCoefficient operator + (LightCoefficient const &lightCoefficient2);
	COLORREF LightCoefficientToRGB();
	int getR();
	int getG();
	int getB();
	void setActive(bool _active);
	bool isAvtive();

private:
	double entries[3];
	bool active;
};

