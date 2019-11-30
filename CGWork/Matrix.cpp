#include "Matrix.h"
#include "stdafx.h"
#include <sstream>
#include <iostream>
#include <string.h>
using namespace std;



Matrix::Matrix()
{
	columns[0] = Vector( 1, 0, 0, 0 );
	columns[1] = Vector( 0, 1, 0, 0 );
	columns[2] = Vector( 0, 0, 1, 0 );
	columns[3] = Vector( 0, 0, 0, 1 );
}
Matrix::Matrix(Vector _column1, Vector _column2, Vector _column3, Vector _column4)
{
	columns[0] = _column1;
	columns[1] = _column2;
	columns[2] = _column3;
	columns[3] = _column4;
}

Matrix::~Matrix(){
}

Matrix Matrix::operator * (Matrix const &matrix2)
{
	Matrix transposed = this->Transpose();
	Matrix result;
	Vector resultColumn;
	// columns of other.
	for (int columnIndex = 0; columnIndex < 4; columnIndex++)
	{
		// rows of self.
		for (int rowIndex = 0; rowIndex < 4; rowIndex++)
		{
			resultColumn[rowIndex] = ( transposed.columns[rowIndex] * matrix2.columns[columnIndex] );
		}
		result.columns[columnIndex] = resultColumn;
	}
	return result;
}

Matrix  Matrix::Transpose() 
{
	Matrix result;
	for (int columnIndex = 0; columnIndex < 4; columnIndex++)
	{
		for (int rowIndex = 0; rowIndex < 4; rowIndex++)
		{
			result.columns[columnIndex][rowIndex] = columns[rowIndex][columnIndex];
		}
	}
	return result;
}

Matrix  Matrix::operator + (const Matrix &matrix2) {
	Matrix result;
	for (int columnIndex = 0; columnIndex < 4; columnIndex++)
	{
		for (int rowIndex = 0; rowIndex < 4; rowIndex++)
		{
			result.columns[columnIndex][rowIndex] = columns[columnIndex][rowIndex] + matrix2.columns[columnIndex][rowIndex];
		}
	}
	return result;
}
Matrix  Matrix::operator - (Matrix const &matrix2)
{
	Matrix result;
	for (int columnIndex = 0; columnIndex < 4; columnIndex++)
	{
		for (int rowIndex = 0; rowIndex < 4; rowIndex++)
		{
			result.columns[columnIndex][rowIndex] = columns[columnIndex][rowIndex] - matrix2.columns[columnIndex][rowIndex];
		}
	}
	return result;
}


Point Matrix::getTranformation(Point p)
{
	Point new_point;
	// columns of other.
	new_point.setX( columns[0][0] * p.getX() + columns[0][1] * p.getY() + columns[0][2] * p.getZ() + columns[0][3] + columns[0][4]);
	new_point.setY( columns[1][0] * p.getX() + columns[1][1] * p.getY() + columns[1][2] * p.getZ() + columns[1][3] + columns[1][4]);
	new_point.setZ( columns[2][0] * p.getX() + columns[2][1] * p.getY() + columns[2][2] * p.getZ() + columns[2][3] + columns[2][4]);
	double w = (columns[3][0] * p.getX() + columns[3][1] * p.getY() + columns[3][2] * p.getZ() + columns[3][3] + columns[3][4]);
	new_point.setX(new_point.getX() / w);
	new_point.setY(new_point.getY() / w);
	new_point.setZ(new_point.getZ() / w);
	return new_point;
}

void Matrix::printMatrix()
{
	string s;
	for (int columnIndex = 0; columnIndex < 4; columnIndex++)
	{
		// rows of self.
		for (int rowIndex = 0; rowIndex < 4; rowIndex++)
		{
			s += to_string(columns[columnIndex][rowIndex])  + "   ";
		}
		s += "\n";
	}

	std::wstring widestr = std::wstring(s.begin(), s.end());
	const wchar_t *c = widestr.c_str();
	AfxMessageBox(c, MB_OK);
}
