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
	void drawPoligons(vector<MyPolygon> polygon_list, COLORREF color, Matrix transformation, CDC* pDC);
	Matrix strechToScreenSize( CRect r);
	Line tranformLine(Line line, Matrix transformationMatrix);
	Point tranformPoint(Point p, Matrix transformationMatrix);
	void updateTransformationObjectSpaceMatricesOfAllObjects(Matrix transformationMatrix);
	void updateTransformationViewSpaceMatricesOfAllObjects(Matrix transformationMatrix);
	void updateTransformationMatrixOfCamera(Matrix transformationMatrix, bool isRotation);
	void setSouldShowBoundingBox(bool _show_bounding_box);
	void setModelColor(COLORREF color);
	void setBoundingBoxColor(COLORREF color);
	void setNormalsColor(COLORREF color);

private:
	std::vector<Model> model_list;
	std::vector<Camera> camera_list;
	void DrawLine(CDC* pDC, Line line, COLORREF _color);
	bool paint_bounding_box;
	COLORREF modelsColor;
	bool isModelColorSet = false;
	COLORREF boundingBoxColor = RGB(1, 0, 0);
	COLORREF normalsColor = RGB(0, 1, 0);
};
