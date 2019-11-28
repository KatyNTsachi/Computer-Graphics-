#include "Scene.h"
#include "MyPolygon.h"

Scene::Scene()
{
	paint_bounding_box = false;
}

Scene::~Scene()
{
}

/// we are scaling every model we bring in 
void Scene::addModel(Model _model)
{
	double MAX_VAL = 1000;
	double min_x = MAX_VAL, max_x = -MAX_VAL, min_y = MAX_VAL, max_y = -MAX_VAL, min_z = MAX_VAL, max_z = -MAX_VAL;

	vector<MyPolygon> polygon_list = _model.getModelPolygons();
	for (auto polygon = polygon_list.begin(); polygon != polygon_list.end(); polygon++)
	{
		vector<Line> line_list = polygon->getLines();
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

			if (max_z < line->getP1().getZ())
				max_z = line->getP1().getZ();
			if (min_z > line->getP1().getZ())
				min_z = line->getP1().getZ();


			//p2
			if (max_x < line->getP2().getX())
				max_x = line->getP2().getX();
			if (min_x > line->getP2().getX())
				min_x = line->getP2().getX();

			if (max_y < line->getP2().getY())
				max_y = line->getP2().getY();
			if (min_y > line->getP2().getY())
				min_y = line->getP2().getY();

			if (max_z < line->getP2().getZ())
				max_z = line->getP2().getZ();
			if (min_z > line->getP2().getZ())
				min_z = line->getP2().getZ();

		}
	}
	_model.setMinMaxValues(min_x, max_x, min_y, max_y, min_z, max_z);
	
	MyPolygon tmp_polygon;
	tmp_polygon.addLine(Line(Point(min_x, min_y, min_z), Point(max_x, min_y, min_z))); tmp_polygon.addLine(Line(Point(max_x, min_y, min_z), Point(max_x, max_y, min_z)));
	tmp_polygon.addLine(Line(Point(max_x, max_y, min_z), Point(min_x, max_y, min_z))); tmp_polygon.addLine(Line(Point(min_x, max_y, min_z), Point(min_x, min_y, min_z)));
	_model.addPolygonToBoundingBox(tmp_polygon);

	tmp_polygon = MyPolygon();
	tmp_polygon.addLine(Line(Point(min_x, min_y, max_z), Point(min_x, max_y, max_z))); tmp_polygon.addLine(Line(Point(min_x, max_y, max_z), Point(max_x, max_y, max_z)));
	tmp_polygon.addLine(Line(Point(max_x, max_y, max_z), Point(max_x, min_y, max_z))); tmp_polygon.addLine(Line(Point(max_x, min_y, max_z), Point(min_x, min_y, max_z)));
	_model.addPolygonToBoundingBox(tmp_polygon);

	tmp_polygon = MyPolygon();
	tmp_polygon.addLine(Line(Point(min_x, min_y, min_z), Point(min_x, max_y, min_z))); tmp_polygon.addLine(Line(Point(min_x, max_y, min_z), Point(min_x, max_y, max_z)));
	tmp_polygon.addLine(Line(Point(min_x, max_y, max_z), Point(min_x, min_y, max_z))); tmp_polygon.addLine(Line(Point(min_x, min_y, max_z), Point(min_x, min_y, min_z)));
	_model.addPolygonToBoundingBox(tmp_polygon);

	tmp_polygon = MyPolygon();
	tmp_polygon.addLine(Line(Point(max_x, min_y, min_z), Point(max_x, max_y, min_z))); tmp_polygon.addLine(Line(Point(max_x, max_y, min_z), Point(max_x, max_y, max_z)));
	tmp_polygon.addLine(Line(Point(max_x, max_y, max_z), Point(max_x, min_y, max_z))); tmp_polygon.addLine(Line(Point(max_x, min_y, max_z), Point(max_x, min_y, min_z)));
	_model.addPolygonToBoundingBox(tmp_polygon);

	tmp_polygon = MyPolygon();
	tmp_polygon.addLine(Line(Point(min_x, min_y, min_z), Point(min_x, min_y, max_z))); tmp_polygon.addLine(Line(Point(min_x, min_y, max_z), Point(max_x, min_y, max_z)));
	tmp_polygon.addLine(Line(Point(max_x, min_y, max_z), Point(max_x, min_y, min_z))); tmp_polygon.addLine(Line(Point(max_x, min_y, min_z), Point(min_x, min_y, min_z)));
	_model.addPolygonToBoundingBox(tmp_polygon);

	tmp_polygon = MyPolygon();
	tmp_polygon.addLine(Line(Point(min_x, max_y, min_z), Point(min_x, max_y, max_z))); tmp_polygon.addLine(Line(Point(min_x, max_y, max_z), Point(max_x, max_y, max_z)));
	tmp_polygon.addLine(Line(Point(max_x, max_y, max_z), Point(max_x, max_y, min_z))); tmp_polygon.addLine(Line(Point(max_x, max_y, min_z), Point(min_x, max_y, min_z)));
	_model.addPolygonToBoundingBox(tmp_polygon);


	double scale_factor;
	if (max_x - min_x > max_y - min_y && max_x - min_x > max_z - min_z)
		scale_factor = max_x - min_x;
	else if(max_y - min_y > max_x - min_x && max_y - min_y > max_z - min_z)
		scale_factor = max_y - min_y;
	else 
		scale_factor = max_z - min_z;

	scale_factor = scale_factor;
	_model.scaleBy(Matrix(	Vector(2 / scale_factor, 0, 0, -(max_x / scale_factor + min_x / scale_factor) ),
									Vector(0, 2 / scale_factor, 0, -(max_y / scale_factor + min_y / scale_factor) ),
									Vector(0, 0, 2 / scale_factor, 0),
									Vector(0, 0, 0, 1)));	
	_model.setShouldBoundingBox(paint_bounding_box);
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

	for (auto tmp_model = model_list.begin(); tmp_model != model_list.end(); tmp_model++) 
	{
		Matrix tmp_camera_trans = camera_list[camera_number].getTransformation();
		Matrix tmp_model_trans = tmp_model->getTransformationMatrix();
		Matrix all_trans = tmp_camera_trans * tmp_model_trans * strechToScreenSize(r);
		
		vector<MyPolygon> model_polygon_list = tmp_model->getModelPolygons();
		drawPoligons(model_polygon_list, tmp_model->getModelColor(), all_trans, pDC);
		if (tmp_model->getShouldBoundingBox() )
		{
			vector<MyPolygon> bounding_box_polygon_list = tmp_model->getBoundingBoxPolygons();
			drawPoligons(bounding_box_polygon_list, tmp_model->getBoundingBoxColor(), all_trans, pDC);
		}
	}
}

void Scene::drawPoligons(vector<MyPolygon> polygon_list, COLORREF color, Matrix transformation, CDC* pDC)
{
	for (auto polygon = polygon_list.begin(); polygon != polygon_list.end(); polygon++)
	{
		vector<Line> line_list = polygon->getLines();
		for (auto line = line_list.begin(); line != line_list.end(); line++)
		{
			Line transformed_line = tranformLine(*line, transformation);

			this->DrawLine(pDC, transformed_line, color);
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

void Scene::updateTransformationObjectSpaceMatricesOfAllObjects(Matrix transformationMatrix)
{

	for (int i = 0; i < model_list.size(); i++) 
		model_list[i].transformInObjectSpace(transformationMatrix);

}

void Scene::updateTransformationViewSpaceMatricesOfAllObjects(Matrix transformationMatrix)
{
	for (int i = 0; i < model_list.size(); i++)
		model_list[i].transformInViewSpace(transformationMatrix);

}


void Scene::updateTransformationMatrixOfCamera(Matrix transformationMatrix, bool isRotation)
{
	for (int i = 0; i < model_list.size(); i++)
	{
		if (isRotation) {
			camera_list[i].rotateByInversOf(transformationMatrix);
		}
		else
		{
			camera_list[i].translateByInversOf(transformationMatrix);
		}
	}
}

void Scene::setModelColor(COLORREF color) 
{
	for (int i = 0; i < model_list.size(); i++)
	{
		model_list[i].setColor(color);
	}
}

void Scene::setBoundingBoxColor(COLORREF color)
{
	for (int i = 0; i < model_list.size(); i++)
	{
		model_list[i].setBoundingBoxColor(color);
	}
}

void Scene::setNormalsColor(COLORREF color)
{
	for (int i = 0; i < model_list.size(); i++)
	{
		model_list[i].setNormalsColor(color);
	}
}

void Scene::setSouldShowBoundingBox(bool _show_bounding_box)
{
	paint_bounding_box = _show_bounding_box;
	for (auto tmp_model = model_list.begin(); tmp_model != model_list.end(); tmp_model++)
	{
		tmp_model->setShouldBoundingBox(_show_bounding_box);
	}
}
