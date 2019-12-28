#include "lightCoefficient.h"

LightCoefficient::LightCoefficient()
{
	entries[0] = 0;
	entries[1] = 0;
	entries[2] = 0;
	active = false;
}

LightCoefficient::LightCoefficient(double x, double y, double z)
{
	entries[0] = x;
	entries[1] = y;
	entries[2] = z;
	active = false;
}

LightCoefficient LightCoefficient::operator * (LightCoefficient const &lightCoefficient2) {
	LightCoefficient lightCoefficient3;
	lightCoefficient3.entries[0] = lightCoefficient2.entries[0] * entries[0];
	lightCoefficient3.entries[1] = lightCoefficient2.entries[1] * entries[1];
	lightCoefficient3.entries[2] = lightCoefficient2.entries[2] * entries[2];
	return lightCoefficient3;
}

LightCoefficient LightCoefficient::operator * (double a)
{
	LightCoefficient lightCoefficient3;
	lightCoefficient3.entries[0] = a * entries[0];
	lightCoefficient3.entries[1] = a * entries[1];
	lightCoefficient3.entries[2] = a * entries[2];
	return lightCoefficient3;
}

LightCoefficient LightCoefficient::operator + (LightCoefficient const &lightCoefficient2) {
	LightCoefficient lightCoefficient3;
	lightCoefficient3.entries[0] = lightCoefficient2.entries[0] + entries[0];
	lightCoefficient3.entries[1] = lightCoefficient2.entries[1] + entries[1];
	lightCoefficient3.entries[2] = lightCoefficient2.entries[2] + entries[2];
	return lightCoefficient3;
}

COLORREF LightCoefficient::LightCoefficientToRGB() {
	int R = entries[0];
	int G = entries[1];
	int B = entries[2];
	int max = max(max(R, G), B);
	//double normalize = (double)255) / max;
	double normalize = 0.80;
	return RGB(int(R * normalize), int(G * normalize), int(B * normalize));
}

LightCoefficient::~LightCoefficient()
{
}

int LightCoefficient::getR()
{
	return entries[0];
}
int LightCoefficient::getG()
{
	return entries[1];
}
int LightCoefficient::getB()
{
	return entries[2];
}
void LightCoefficient::setActive(bool _active)
{
	active = _active;
}

bool LightCoefficient::isAvtive()
{
	return active;
}