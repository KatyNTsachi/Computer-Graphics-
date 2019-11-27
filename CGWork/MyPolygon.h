#pragma once

#include "Point.h"
#include "Line.h"
#include <vector>
#include "stdafx.h"

class MyPolygon
{

public:
	MyPolygon();
	~MyPolygon();
	void addLine(Line line);
	std::vector<Line> getLines();

private:
	std::vector<Line> lines;
};

