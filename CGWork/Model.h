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
	std::vector<MyPolygon> getBoundingBoxPolygons();
	void addPolygon(MyPolygon polygon);
	void addPolygonToBoundingBox(MyPolygon _polygon);
	void setColor(COLORREF _color);
	void setColor(int RGB[]);
	void setBoundingBoxColor(COLORREF _color);
	void setNormalsColor(COLORREF _color);
	COLORREF getBoundingBoxColor();
	COLORREF getModelColor();
	Matrix getTransformationMatrix();
	void scaleBy(Matrix scale_matrix);
	void transformInObjectSpace(Matrix transformationMatrix);
	void transformInViewSpace(Matrix _transformationnMatrix);
	void setMinMaxValues(double min_x, double max_x, double min_y, double max_y, double min_z, double max_z);
	void setShouldBoundingBox(bool _print_bounding_box);
	bool getShouldBoundingBox();

private:
	std::vector<MyPolygon> polygon_list;
	std::vector<MyPolygon> bounding_box_polygon_list;

	Matrix objectSpaceTransformation;
	Matrix sceenSpaceTransformation;

	COLORREF color = RGB(0, 0, 0);
	COLORREF boundingBoxColor = RGB(1, 0, 0);
	COLORREF normalsColor = RGB(0, 1, 0);
	double min_x, max_x, min_y, max_y, min_z, max_z;
	bool paint_bounding_box;
};

