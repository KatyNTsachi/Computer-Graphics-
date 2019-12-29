#pragma once

#include"Line.h"
#include"Matrix.h"
#include <iostream>
#include <vector>
#include "stdafx.h"
#include "MyPolygon.h"
#include "lightCoefficient.h"

#include <unordered_map>

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
	void transformInObjectSpace(Matrix transformationMatrix);
	void transformInViewSpace(Matrix _transformationnMatrix);
	void setMinMaxValues(double min_x, double max_x, double min_y, double max_y, double min_z, double max_z);
	void getMinMaxValues(double &_min_x, double &_max_x, double &_min_y, double &_max_y, double &_min_z, double &_max_z);
	void setShouldBoundingBox(bool _print_bounding_box);
	bool getShouldBoundingBox();
	void addNormals();
	std::vector<Line> getOriginalVertexNormalList();
	std::vector<Line> getCalculatedVertexNormalList();
	std::vector<Line> getOriginalPolygonNormalList();
	std::vector<Line> getCalculatedPolygonNormalList();
	std::vector<Line> getSilhouetteLinesList(Matrix transformation);
	void setListOfPolygons(std::vector<MyPolygon> _list_of_polygons);
	COLORREF getNormalsColor();

	LightCoefficient k_d = LightCoefficient(1, 1, 1);
	LightCoefficient k_s = LightCoefficient(1, 1, 1);
	int specularityExponent = 1;

private:
	std::vector<MyPolygon> polygon_list;
	std::vector<MyPolygon> bounding_box_polygon_list;
	std::vector<Line> polygon_original_normal_list;
	std::vector<Line> polygon_calculated_normal_list;
	std::vector<Line> vertex_original_normal_list;
	std::vector<Line> vertex_calculated_normal_list;


	Matrix objectSpaceTransformation;
	Matrix sceenSpaceTransformation;

	COLORREF color = RGB(0, 0, 0);
	COLORREF boundingBoxColor = RGB(1, 0, 0);
	COLORREF normalsColor = RGB(0, 1, 0);
	double min_x, max_x, min_y, max_y, min_z, max_z;
	bool paint_bounding_box;
};

