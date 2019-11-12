#pragma once

#include"Line.h"
#include"Matrix.h"
#include <iostream>
#include <vector>

using namespace std;

class Model
{
public:
	Model(std::vector<Line> _line_list);
	~Model();
	std::vector<Line> getModelLines(Matrix camera_transformation);
	
private:
	std::vector<Line> line_list;
	Matrix transformation;
};

