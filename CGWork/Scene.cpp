#include "Scene.h"



Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::AddModel(Model _model)
{
	model_list.push_back(_model);
}

void Scene::Draw(CDC* pDC) {

	std::vector<Line> model_lines;
	Matrix tmp;

	for (auto tmp_model = model_list.begin(); tmp_model != model_list.end(); tmp_model++ )
	{
		model_lines = tmp_model->getModelLines(tmp);
		
		for (auto tmp_line = model_lines.begin(); tmp_line != model_lines.end(); tmp_line++)
		{
			this->DrawLine(pDC, *tmp_line);
		}

	}

}



void Scene::DrawLine(CDC* pDC, Line line) {
	
	COLORREF color = RGB(0, 0, 0);

	for (int i = 1; i < 100; i++)
		pDC->SetPixel(i, i, color);

}