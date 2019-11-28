#pragma once

#include"Line.h"
#include"Matrix.h"
#include <iostream>
#include <vector>
#include "stdafx.h"
#include "Poligon.h"

using namespace std;

class Model
{
public:
	Model();
	~Model();
	std::vector<Poligon> getModelPoligons();
	void addPoligon(Poligon poligon);
	void setColor(COLORREF _color);
	void setColor(int RGB[]);
	COLORREF getModelColor();
	Matrix getTransformationMatrix();
	void scaleBy(Matrix scale_matrix);
	void rotateBy(Matrix rotationMatrix);
	void translateBy(Matrix affainMatrix);
private:
	std::vector<Poligon> poligon_list;
	Matrix rotationTransformation;
	Matrix affainTransformation;
	COLORREF color = RGB(0, 0, 0);

};

