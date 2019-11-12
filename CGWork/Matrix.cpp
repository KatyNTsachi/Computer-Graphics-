#include "Matrix.h"




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

