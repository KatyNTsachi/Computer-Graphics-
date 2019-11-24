#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::addModel(Model _model)
{
	double MAX_VAL = 1000;
	double min_x = MAX_VAL, max_x = -MAX_VAL, min_y = MAX_VAL, max_y = -MAX_VAL;

	vector<Poligon> poligon_list = _model.getModelPoligons();
	for (auto poligon = poligon_list.begin(); poligon != poligon_list.end(); poligon++)
	{
		vector<Line> line_list = poligon->getLines();
		for (auto line = line_list.begin(); line != line_list.end(); line++)
		{
			if (max_x < line->getP1().getX())
				max_x = line->getP1().getX();
			if (min_x > line->getP1().getX())
				min_x = line->getP1().getX();

			if (max_y < line->getP1().getY())
				max_y = line->getP1().getY();
			if (min_y > line->getP1().getY())
				min_y = line->getP1().getY();

			//p2
			if (max_x < line->getP2().getX())
				max_x = line->getP2().getX();
			if (min_x > line->getP2().getX())
				min_x = line->getP2().getX();

			if (max_y < line->getP2().getY())
				max_y = line->getP2().getY();
			if (min_y > line->getP2().getY())
				min_y = line->getP2().getY();
		}
	}

	double scale_factor;
	if (max_x - min_x > max_y - min_y)
		scale_factor = max_x - min_x;
	else
		scale_factor = max_y - min_y;

	scale_factor = scale_factor;
	_model.addScaleMatrix(Matrix(	Vector(2 / scale_factor, 0, 0, -(max_x / scale_factor + min_x / scale_factor) ),
									Vector(0, 2 / scale_factor, 0, -(max_y / scale_factor + min_y / scale_factor) ),
									Vector(0, 0, 2 / scale_factor, 0),
									Vector(0, 0, 0, 1)));

	model_list.push_back(_model);
}

void Scene::AddCamera(Camera _camera)
{
	camera_list.push_back(_camera);
}

void Scene::Draw(CDC* pDC, int camera_number, CRect r) {

	//error messege
	if (camera_number > camera_list.size() - 1)
	{
		std::string  s = "we dont have this camera";
		std::wstring widestr = std::wstring(s.begin(), s.end());
		const wchar_t *c = widestr.c_str();
		AfxMessageBox(c, MB_OK);
		return;
	}
	
	std::vector<Line> model_lines;
	Matrix tmp;


	Point p1;
	Point p2;
	Line tmpl(p1, p2);


	COLORREF color = (255, 0, 0);
	

	for (auto tmp_model = model_list.begin(); tmp_model != model_list.end(); tmp_model++) 
	{
		Matrix tmp_camera_trans = camera_list[camera_number].getTransformation();
		Matrix tmp_model_trans = tmp_model->getTransformationMatrix();
		Matrix all_trans = tmp_camera_trans * tmp_model_trans * strechToScreenSize(r);
		

		vector<Poligon> poligon_list = tmp_model->getModelPoligons();
		for (auto poligon = poligon_list.begin(); poligon != poligon_list.end(); poligon++)
		{
			vector<Line> line_list = poligon->getLines();
			for (auto line = line_list.begin(); line != line_list.end(); line++)
			{
				Line transformed_line = tranformLine(*line, all_trans);

				this->DrawLine(pDC, transformed_line, color);
			}
		}
	}
}

Matrix Scene::strechToScreenSize( CRect r)
{
	int width = abs(r.right - r.left);
	int height = abs(r.bottom - r.top);
	
	return Matrix(Vector(width / 2, 0, 0, width / 2),
				  Vector(0, height / 2, 0, height / 2),
				  Vector(0, 0, 1, 0),
				  Vector(0, 0, 0, 1));
	

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

Line Scene::tranformLine(Line line, Matrix transformationMatrix)
{
	Point new_p1, new_p2;
	new_p1 = tranformPoint(line.getP1(), transformationMatrix);
	new_p2 = tranformPoint(line.getP2(), transformationMatrix);
	Line tranformed_line(new_p1, new_p2);
	   
	return tranformed_line;
}

Point Scene::tranformPoint(Point p, Matrix transformationMatrix)
{
	Point tranformed_point;
	//transformations.printMatrix();
	tranformed_point = transformationMatrix.getTranformation(p);

	return tranformed_point;
}

void Scene::updateTransformationMatricesOfAllObjects(Matrix transformationMatrix, bool isRotation)
{
	for (int i = 0; i < model_list.size(); i++) 
	{
		if (isRotation) {
			model_list[i].rotateBy(transformationMatrix);
		}
		else
		{
			model_list[i].translateBy(transformationMatrix);
		}
	}
}

void Scene::updateTransformationMatrixOfCamera(Matrix transformationMatrix, bool isRotation)
{

}
