#include "antiAliasing.h"


void antiAliasing::blur(int view_mat[], int width, int height, int kernal_size, int kernal_type)
{

}

std::vector<double> antiAliasing::getKernal(int kernal_size, kernalTypes kernal_type)
{
	if (kernal_type == BOX)
	{
		return getBoxKernalOfSize(kernal_size);
	}
	else if (kernal_type == TRIANGLE)
	{
		return getTriangleKernalOfSize(kernal_size);
	}
	else if (kernal_type == GAUSSIAN)
	{
		return getGaussianKernalOfSize(kernal_size);
	}
	else // SINC
	{
		return getSincKernalOfSize(kernal_size);
	}
}

std::vector<double> antiAliasing::getRelevantPixels(int view_mat[], int width, int height, int x, int y, int kernal_size)
{
	std::vector<double>
}

double getMul(std::vector<double> &relevant_pixels, std::vector<double> &kernal)
{

}

std::vector<double> antiAliasing::getBoxKernalOfSize(int kernal_size)
{
	double val = 1.0 / 9;
	return std::vector<double>(val, val, val, val, val, val, val, val, val);
	/*
	if (kernal_size == 3)
	{
		double val = 1.0 / 9;
		return std::vector(val, val, val, val, val, val, val, val, val);
	}
	else
	{
		double val = 1.0 / 25;
		return std::vector(val, val, val, val, val, val, val, val, val, );
	}
	*/
}
std::vector<double> antiAliasing::getTriangleKernalOfSize(int kernal_size)
{
	return getBoxKernalOfSize(kernal_size);
}
std::vector<double> antiAliasing::getGaussianKernalOfSize(int kernal_size)
{
	return getBoxKernalOfSize(kernal_size);
}
std::vector<double> antiAliasing::getSincKernalOfSize(int kernal_size)
{
	return getBoxKernalOfSize(kernal_size);
}
