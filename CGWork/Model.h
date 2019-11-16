#pragma once

#include"Line.h"
#include"Matrix.h"
#include <iostream>
#include <vector>
#include "stdafx.h"

using namespace std;

class Model
{
public:
	Model();
	Model(std::vector<Line> _line_list);
	~Model();
	std::vector<Line> getModelLines(Matrix camera_transformation);
	void addLine(Line _line);
	void setColor(COLORREF _color);
	void setColor(int RGB[]);
	COLORREF getModelColor();

private:
	std::vector<Line> line_list;
	Matrix transformation;
	COLORREF color = RGB(0, 0, 0);

};

