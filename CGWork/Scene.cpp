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
	COLORREF color;

	for (auto tmp_model = model_list.begin(); tmp_model != model_list.end(); tmp_model++ )
	{
		model_lines = tmp_model->getModelLines(tmp);
		color = tmp_model->getModelColor();

		for (auto tmp_line = model_lines.begin(); tmp_line != model_lines.end(); tmp_line++)
		{
			this->DrawLine(pDC, *tmp_line, color);
		}

	}

}



void Scene::DrawLine(CDC* pDC, Line line, COLORREF _color) {
	
	COLORREF color = _color;
	Point p1 = line.getP1();
	Point p2 = line.getP2();
	Point tmp_p;
	double dy, dx, d, d_e, d_ne;
	int x, y;
	int tmp_x, tmp_y;

	int opposite = 1;
	bool slope_too_big = false;
	bool slope_negative = false;


	//set dx and dy
	dy = (p2.getY() - p1.getY());
	dx = (p2.getX() - p1.getX());

	//is the slope bigger then 1?
	if (abs(dy) > abs(dx))
	{
		//change p1
		//we want to change the axis
		tmp_p = p1;
		p1.setX(tmp_p.getY());
		p1.setY(tmp_p.getX());
		
		//change p2
		tmp_p = p2;
		p2.setX(tmp_p.getY());
		p2.setY(tmp_p.getX());

		//corrent dx and dy
		dx = (p2.getX() - p1.getX());
		dy = (p2.getY() - p1.getY());


		//set flag
		slope_too_big = true;
	}

	// p2.x should be bigger the p1.x
	if (p1.getX() > p2.getX())
	{
		tmp_p = p1;
		p1 = p2;
		p2 = tmp_p;

		//set dx and dy
		dy = (p2.getY() - p1.getY());
		dx = (p2.getX() - p1.getX());
	}


	if (dy < 0)
	{
		//change p1
		p2.setY(p1.getY() - dy);

		//corrent dy
		dy = (p2.getY() - p1.getY());

		//set flag
		slope_negative = true;
	}


	//init d, d_e, d_ne
	d = 2 * dy - dx;
	d_e = 2 * dy;
	d_ne = 2 * (dy - dx);

	//init x and y
	x = p1.getX();
	y = p1.getY();

	while (x < int(p2.getX()))
	{
		
		//decide which way to go
		if (d < 0)
		{
			d = d + d_e;	
			x = x + 1;
		}

		else
		{
			d = d + d_ne;
			x = x + 1;
			y = y + 1;
		}

		//print

		//negative slope 
		tmp_x = x;
		tmp_y = y;

		if( slope_negative == true )
		{
			tmp_y = int(2 * p1.getY() - tmp_y);
		}

		
		//slope is too big
		if( slope_too_big == false )
			pDC->SetPixel(tmp_x, tmp_y, color);
		else
			pDC->SetPixel(tmp_y, tmp_x, color);

	}		

}