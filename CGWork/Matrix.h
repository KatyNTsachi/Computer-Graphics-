#pragma once
#include "Vector.h"
#include <iostream>
#include <vector>
#include "Point.h"

# define NUM_OF_VECTORS 4
class Matrix
{
public:
	Matrix(Vector _column1, Vector _column2, Vector _column3, Vector _column4);
	Matrix();
	~Matrix();
	Matrix operator * (Matrix const &matrix2);
	Matrix operator + (Matrix const &matrix2);
	Matrix operator - (Matrix const &matrix2);
	Matrix Transpose();
	Point getTranformation(Point p);
	void printMatrix();

	Vector columns[NUM_OF_VECTORS];
	
};

