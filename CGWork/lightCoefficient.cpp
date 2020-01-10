#include "lightCoefficient.h"

LightCoefficient::LightCoefficient()
{
	entries[0] = 0;
	entries[1] = 0;
	entries[2] = 0;
	active = false;
	entries_shine[0] = 0;
	entries_shine[1] = 0;
	entries_shine[2] = 0;

	entries_fog[0] = 0;
	entries_fog[1] = 0;
	entries_fog[2] = 0;

}

LightCoefficient::LightCoefficient(double x, double y, double z)
{
	entries[0] = x;
	entries[1] = y;
	entries[2] = z;
	active = false;
	entries_shine[0] = 0;
	entries_shine[1] = 0;
	entries_shine[2] = 0;

	entries_fog[0] = 0;
	entries_fog[1] = 0;
	entries_fog[2] = 0;


}

LightCoefficient::LightCoefficient(double x, double y, double z, double _alpha)
{
	entries[0] = x;
	entries[1] = y;
	entries[2] = z;
	alpha = _alpha;
	active = false;
	entries_shine[0] = 0;
	entries_shine[1] = 0;
	entries_shine[2] = 0;

	entries_fog[0] = 0;
	entries_fog[1] = 0;
	entries_fog[2] = 0;

}

LightCoefficient::LightCoefficient(const LightCoefficient &old_obj)
{
	entries[0] = old_obj.entries[0];
	entries[1] = old_obj.entries[1];
	entries[2] = old_obj.entries[2];
	active = old_obj.active;
	alpha = old_obj.alpha;
	entries_shine[0] = old_obj.entries_shine[0];
	entries_shine[1] = old_obj.entries_shine[1];
	entries_shine[2] = old_obj.entries_shine[2];

	entries_fog[0] = old_obj.entries_fog[0];
	entries_fog[1] = old_obj.entries_fog[1];
	entries_fog[2] = old_obj.entries_fog[2];

}

LightCoefficient LightCoefficient::operator * (LightCoefficient const &lightCoefficient2) {
	LightCoefficient lightCoefficient3;
	lightCoefficient3.entries[0] = lightCoefficient2.entries[0] * entries[0];
	lightCoefficient3.entries[1] = lightCoefficient2.entries[1] * entries[1];
	lightCoefficient3.entries[2] = lightCoefficient2.entries[2] * entries[2];

	lightCoefficient3.entries_shine[0] = lightCoefficient2.entries_shine[0] * entries_shine[0];
	lightCoefficient3.entries_shine[1] = lightCoefficient2.entries_shine[1] * entries_shine[1];
	lightCoefficient3.entries_shine[2] = lightCoefficient2.entries_shine[2] * entries_shine[2];

	lightCoefficient3.entries_fog[0] = lightCoefficient2.entries_fog[0] * entries_fog[0];
	lightCoefficient3.entries_fog[1] = lightCoefficient2.entries_fog[1] * entries_fog[1];
	lightCoefficient3.entries_fog[2] = lightCoefficient2.entries_fog[2] * entries_fog[2];


	return lightCoefficient3;
}

LightCoefficient LightCoefficient::operator * (double a)
{
	LightCoefficient lightCoefficient3;
	lightCoefficient3.entries[0] = a * entries[0];
	lightCoefficient3.entries[1] = a * entries[1];
	lightCoefficient3.entries[2] = a * entries[2];

	lightCoefficient3.entries_shine[0] = a * entries_shine[0];
	lightCoefficient3.entries_shine[1] = a * entries_shine[1];
	lightCoefficient3.entries_shine[2] = a * entries_shine[2];

	lightCoefficient3.entries_fog[0] = a * entries_fog[0];
	lightCoefficient3.entries_fog[1] = a * entries_fog[1];
	lightCoefficient3.entries_fog[2] = a * entries_fog[2];


	lightCoefficient3.alpha = alpha;

	return lightCoefficient3;
}

LightCoefficient LightCoefficient::multiplyColorOnly(double a)
{
	LightCoefficient lightCoefficient3;
	lightCoefficient3.entries[0] = a * entries[0];
	lightCoefficient3.entries[1] = a * entries[1];
	lightCoefficient3.entries[2] = a * entries[2];

	lightCoefficient3.entries_shine[0] = entries_shine[0];
	lightCoefficient3.entries_shine[1] = entries_shine[1];
	lightCoefficient3.entries_shine[2] = entries_shine[2];

	lightCoefficient3.entries_fog[0] = entries_fog[0];
	lightCoefficient3.entries_fog[1] = entries_fog[1];
	lightCoefficient3.entries_fog[2] = entries_fog[2];

	lightCoefficient3.alpha = alpha;

	return lightCoefficient3;
}

LightCoefficient LightCoefficient::operator + (LightCoefficient const &lightCoefficient2) {
	LightCoefficient lightCoefficient3;
	lightCoefficient3.entries[0] = lightCoefficient2.entries[0] + entries[0];
	lightCoefficient3.entries[1] = lightCoefficient2.entries[1] + entries[1];
	lightCoefficient3.entries[2] = lightCoefficient2.entries[2] + entries[2];

	lightCoefficient3.entries_shine[0] = lightCoefficient2.entries_shine[0] + entries_shine[0];
	lightCoefficient3.entries_shine[1] = lightCoefficient2.entries_shine[1] + entries_shine[1];
	lightCoefficient3.entries_shine[2] = lightCoefficient2.entries_shine[2] + entries_shine[2];

	lightCoefficient3.entries_fog[0] = lightCoefficient2.entries_fog[0] + entries_fog[0];
	lightCoefficient3.entries_fog[1] = lightCoefficient2.entries_fog[1] + entries_fog[1];
	lightCoefficient3.entries_fog[2] = lightCoefficient2.entries_fog[2] + entries_fog[2];

	lightCoefficient3.alpha = alpha;


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
double LightCoefficient::getAlpha()
{
	return alpha;
}
void LightCoefficient::setActive(bool _active)
{
	active = _active;
}

bool LightCoefficient::isActive()
{
	return active;
}

void LightCoefficient::setAlpha(double _alpha)
{
	alpha = _alpha;
}


void LightCoefficient::setShine(double x, double y, double z)
{
	entries_shine[0] = x;
	entries_shine[1] = y;
	entries_shine[2] = z;
}

LightCoefficient LightCoefficient::getShine()
{
	return LightCoefficient(entries_shine[0], entries_shine[1], entries_shine[2]);
}


void LightCoefficient::setFog(double x, double y, double z)
{
	entries_fog[0] = x;
	entries_fog[1] = y;
	entries_fog[2] = z;
}

LightCoefficient LightCoefficient::getFog()
{
	return LightCoefficient(entries_fog[0], entries_fog[1], entries_fog[2]);
}


void LightCoefficient::cutColorBigValues()
{
	entries[0] = entries[0] > 255 ? 255 : entries[0];
	entries[1] = entries[1] > 255 ? 255 : entries[1];
	entries[2] = entries[2] > 255 ? 255 : entries[2];

}