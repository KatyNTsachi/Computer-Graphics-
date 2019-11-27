#pragma once

#include"Line.h"
#include"Matrix.h"
#include <iostream>
#include <vector>
#include "stdafx.h"
#include "MyPolygon.h"

using namespace std;

class Model
{
public:
	Model();
	~Model();
	std::vector<MyPolygon> getModelPolygons();
	void addPolygon(MyPolygon polygon);
	void addPolygonToBoundingBox(MyPolygon _polygon);
	void setColor(COLORREF _color);
	void setColor(int RGB[]);
	COLORREF getModelColor();
	Matrix getTransformationMatrix();
	void addScaleMatrix(Matrix scale_matrix);
	void rotateBy(Matrix rotationMatrix);
	void translateBy(Matrix affainMatrix);
	void setMinMaxValues(double min_x, double max_x, double min_y, double max_y, double min_z, double max_z);
	void paintBoundingBox(bool _print_bounding_box);

private:
	std::vector<MyPolygon> polygon_list;
	std::vector<MyPolygon> bounding_box_polygon_list;

	Matrix rotationTransformation;
	Matrix affainTransformation;
	COLORREF color = RGB(0, 0, 0);
	double min_x, max_x, min_y, max_y, min_z, max_z;
	bool paint_bounding_box;

};

