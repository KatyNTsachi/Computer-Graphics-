#pragma once

#include "Point.h"
#include "Line.h"
#include <vector>
#include "stdafx.h"
#include "Vector.h"

class MyPolygon
{

public:
	MyPolygon();
	~MyPolygon();
	void addLine(Line line);
	std::vector<Line>& getLines();
	void setCenter(Point _p);
	Point getCenter();
	void setOriginalNormal(Vector _normal);
	void setCalculatedNormal(Vector _normal);
	Vector getOriginalNormal(bool show_regular_normals);
	Vector getCalculatedNormal(bool show_regular_normals);
	void setListOfLines(std::vector<Line> _list_of_lines);
	MyPolygon tranformPolygon(Matrix transformationMatrix);
	
private:
	std::vector<Line> lines;
	Vector original_normal;
	Vector calculated_normal;
	Point center_of_polygon;
	Vector flipOrNot(Vector &v, bool show_regular_normals);

};

