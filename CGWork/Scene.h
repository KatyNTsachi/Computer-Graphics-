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
	void AddModel(Model _model);
	void Draw(CDC* pDC);

private:
	std::vector<Model> model_list;
	std::vector<Camera> camera_list;
	void DrawLine(CDC* pDC, Line line, COLORREF _color);
};

