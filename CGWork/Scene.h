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
	void Draw(CDC* pDC, int camera_number, CRect r, int view_mat[]);
	void drawPoligons(vector<MyPolygon> polygon_list, COLORREF color, Matrix transformation, CDC* pDC, int view_mat[]);
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
	bool paint_vertex_normals = false;
	bool paint_polygon_normals = false;

private:
	std::vector<Model> model_list;
	std::vector<Camera> camera_list;
	void drawLine(CDC* pDC, Line line, COLORREF _color, int view_mat[]);
	void drawLines(CDC* pDC, vector<Line> line, COLORREF _color, Matrix _transformation, int view_mat[]);
	bool paint_bounding_box;
	COLORREF modelsColor;
	bool isModelColorSet = false;
	COLORREF boundingBoxColor = RGB(1, 0, 0);
	COLORREF normalsColor = RGB(0, 1, 0);
	void calcModelMinMax(Model &_model);
	void addBoundingBox(Model &_model);
	void normalizeTheModel(Model &_model);
	void setModelColor(Model &_model);
	int height, width;
};
