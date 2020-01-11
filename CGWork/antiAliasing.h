#pragma once
#include <iostream>
#include "stdafx.h"
#include <vector>
#include "CGWorkDefines.h"

class antiAliasing
{
public:
	static void blur(int view_mat[], int width,int height,int kernal_size, int kernal_type);

private:
	static std::vector<double> getKernal(int kernal_size, kernalTypes kernal_type);
	static std::vector<double> getRelevantPixels(int view_mat[], int width, int height, int x, int y, int kernal_size);
	static double getMul(std::vector<double> &relevant_pixels, std::vector<double> &kernal);
	static std::vector<double> getBoxKernalOfSize(int kernal_size);
	static std::vector<double> getTriangleKernalOfSize(int kernal_size);
	static std::vector<double> getGaussianKernalOfSize(int kernal_size);
	static std::vector<double> getSincKernalOfSize(int kernal_size);
};

