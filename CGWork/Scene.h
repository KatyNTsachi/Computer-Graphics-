#pragma once
#include <iostream>
#include <vector>

#include"Model.h"
#include"Camera.h"

//for the CDC
#include "stdafx.h"

class Scene
{
public:
	Scene();
	~Scene();
	void addModel(Model _model);
	void AddCamera(Camera _camera);
	void Draw(CDC* pDC, int camera_number, CRect r);
	Matrix strechToScreenSize( CRect r);
	Line tranformLine(Line line, Matrix transformationMatrix);
	Point tranformPoint(Point p, Matrix transformationMatrix);
	void updateTransformationMatricesOfAllObjects(Matrix transformationMatrix, bool isRotation);
	void updateTransformationMatrixOfCamera(Matrix transformationMatrix, bool isRotation);
	void showBoundingBox(bool _show_bounding_box);

private:
	std::vector<Model> model_list;
	std::vector<Camera> camera_list;
	void DrawLine(CDC* pDC, Line line, COLORREF _color);
};
