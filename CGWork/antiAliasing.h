#pragma once
#include <iostream>
#include "stdafx.h"
#include <vector>

class antiAliasing
{
public:
	static void blur(int view_mat[], int width,int height,int kernal_size, int kernal_type);

private:
	static std::vector<double> getKernal(int kernal_size, int kernal_type);
	static std::vector<double> getRelevantPixels(int view_mat[], int width, int height, int x, int y, int kernal_size);
	static double getMul(std::vector<double> &relevant_pixels, std::vector<double> &kernal);
};

