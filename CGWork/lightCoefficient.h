#pragma once
#include "stdafx.h"

class LightCoefficient
{
public:
	LightCoefficient();
	LightCoefficient::LightCoefficient(double x, double y, double z);
	LightCoefficient::LightCoefficient(double x, double y, double z, double _alpha);
	LightCoefficient(const LightCoefficient &old_obj);
	~LightCoefficient();
	LightCoefficient operator * (LightCoefficient const &lightCoefficient2);
	LightCoefficient operator * (double a);
	LightCoefficient multiplyColorOnly(double a);

	LightCoefficient operator + (LightCoefficient const &lightCoefficient2);
	COLORREF LightCoefficientToRGB();
	int getR();
	int getG();
	int getB();
	double getAlpha();
	void setActive(bool _active);
	bool isActive();
	void setShine(double x, double y, double z);
	LightCoefficient getShine();


private:
	double entries[3];
	double entries_shine[3];
	double alpha = 0.5;

	bool active;
};

