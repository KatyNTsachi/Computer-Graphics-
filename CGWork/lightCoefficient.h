#pragma once
#include "stdafx.h"

class LightCoefficient
{
public:
	LightCoefficient();
	LightCoefficient::LightCoefficient(double x, double y, double z);
	~LightCoefficient();
	COLORREF LightCoefficient::operator * (LightCoefficient const &lightCoefficient2);
private:
	double entries[3];
};

