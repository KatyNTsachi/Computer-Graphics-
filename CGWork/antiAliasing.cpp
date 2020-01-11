#include "antiAliasing.h"

int[] antiAliasing::blur(int* view_mat, int width, int height, int kernal_size, kernalTypes kernal_type)
{
	std::vector<LightCoefficient> * tmp_view_mat = new std::vector<LightCoefficient>[height*width];
	std::vector<double> kernal_vec = getKernal(kernal_size, kernal_type);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			std::vector<LightCoefficient> relevant_pixels = getRelevantPixels(view_mat, width, height, i, j, kernal_size);
			tmp_view_mat[i * width + j].push_back(getMul(relevant_pixels, kernal_vec));
		}
	}

	//copy tmp_view_mat to view_mat
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			view_mat[i * width + j][0] = tmp_view_mat[i * width + j][0];
		}
	}

	delete[] tmp_view_mat;
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

std::vector<LightCoefficient> antiAliasing::getRelevantPixels(std::vector<LightCoefficient> * view_mat, int width, int height, int x, int y, int kernal_size)
{
	int num_of_kernal_pixels = pow(kernal_size, 2);
	std::vector<LightCoefficient> ret_vec;
	int range_of_loop = kernal_size / 2;
	int counter = 0;
	for (int i = -range_of_loop; i <= range_of_loop; i++)
	{
		for (int j = -range_of_loop; j <= range_of_loop; j++)
		{
			int curr_x = x + i;
			int curr_y = y + j;
			if (curr_x >= 0 && curr_y >= 0 && curr_x < height && curr_y < width)
			{
				ret_vec.push_back(view_mat[curr_x * width + curr_y][0]);
			}
			else
			{
				ret_vec.push_back(LightCoefficient(0, 0, 0));
			}
		}
	}
	return ret_vec;
}




std::vector<double> antiAliasing::getBoxKernalOfSize(int kernal_size)
{
	double val = 1.0 / 9;
	//std::vector<double> ret_vec = { val, val, val, val, val, val, val, val, val };
	std::vector<double> ret_vec = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	return ret_vec;
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

LightCoefficient antiAliasing::getMul(std::vector<LightCoefficient> &relevant_pixels, std::vector<double> &kernal)
{

	LightCoefficient res = LightCoefficient(0, 0, 0);
	for (int i = 0; i < relevant_pixels.size(); i++)
			res = res + relevant_pixels[i] * kernal[i];
	return res;
}	
