#include "Scene.h"
#include "MyPolygon.h"
#include "Transformations.h"
#include "ParallelLightSource.h"
#include "CGWorkDefines.h"


Scene::Scene()
{
	paint_bounding_box = false;
	show_original_normals = true;
	shadingType = FLAT_SHADING;
	ParallelLightSource *parallelLightSource = new ParallelLightSource(Vector(1, 0, 0, 0));
	lightSources[0] = (parallelLightSource);
}

Scene::~Scene()
{
}

void Scene::calcModelMinMax(Model &_model)
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

}

void Scene::addBoundingBox(Model &_model)
{
	double min_x, min_y, min_z, max_x, max_y, max_z;
	_model.getMinMaxValues(min_x, max_x, min_y, max_y, min_z, max_z);

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
}

void Scene::normalizeTheModel(Model &_model)
{
	double min_x, min_y, min_z, max_x, max_y, max_z;
	_model.getMinMaxValues(min_x, min_y, min_z, max_x, max_y, max_z);

	double scale_factor;
	if (max_x - min_x > max_y - min_y && max_x - min_x > max_z - min_z)
		scale_factor = max_x - min_x;
	else if (max_y - min_y > max_x - min_x && max_y - min_y > max_z - min_z)
		scale_factor = max_y - min_y;
	else
		scale_factor = max_z - min_z;

	scale_factor = scale_factor;
	_model.transformInObjectSpace(Matrix(	Vector(2 / scale_factor, 0, 0, -(max_x / scale_factor + min_x / scale_factor)),
							Vector(0, 2 / scale_factor, 0, -(max_y / scale_factor + min_y / scale_factor)),
							Vector(0, 0, 2 / scale_factor, 0),
							Vector(0, 0, 0, 1)));
}

void Scene::setModelColor(Model &_model)
{
	if (isModelColorSet)
		_model.setColor(modelsColor);

	_model.setBoundingBoxColor(boundingBoxColor);
	_model.setNormalsColor(normalsColor);
}

 void Scene::highlightModel(COLORREF _color, int modelIndex)
{
	 COLORREF hilightedColor = getFaddedModelColor(modelIndex);

	 if (hilightedModelIndex != -1)
	 {
		 unHighlightModel();
	 }

	 hilightedModelIndex = modelIndex;
	 originalColorOfHighlitedModel = model_list[modelIndex].getModelColor();
	 model_list[modelIndex].setColor(hilightedColor);
}

COLORREF Scene::getFaddedModelColor(int modelIndex)
{
	COLORREF originalColor;
	if (isModelColorSet)
	{
		originalColor = getModelColor();
	}
	else
	{
		originalColor = model_list[modelIndex].getModelColor();
	}
	double alpha = 0.3;
	COLORREF hilightedColor = RGB(alpha * GetRValue(originalColor) + (1 - alpha) * 255,
		alpha * GetGValue(originalColor) + (1 - alpha) * 255,
		alpha * GetBValue(originalColor) + (1 - alpha) * 255);
	return hilightedColor;
}

COLORREF Scene::getModelColor()
{
	return modelsColor;
}

void Scene::unHighlightModel()
{
	model_list[hilightedModelIndex].setColor(originalColorOfHighlitedModel);
	setModelColor(model_list[hilightedModelIndex]);
	hilightedModelIndex = -1;
}

/// we are scaling every model we bring in 
void Scene::addModel(Model _model)
{

	setModelColor(_model);

	calcModelMinMax(_model);
	
	normalizeTheModel(_model);
	
	addBoundingBox(_model);

	_model.setShouldBoundingBox(paint_bounding_box);

	_model.addNormals();

	model_list.push_back(_model);
}

void Scene::AddCamera(Camera _camera)
{
	camera_list.push_back(_camera);
}

void Scene::Draw(CDC* pDC, int camera_number, CRect r, int view_mat[], double z_buffer[], double tmp_drawing_view_mat[]) {

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
		Matrix all_trans = getTransformationMatrix(*tmp_model, camera_number, r);

		vector<MyPolygon> model_polygon_list = tmp_model->getModelPolygons();
		drawPolygons(*tmp_model, model_polygon_list, tmp_model->getModelColor(), all_trans, pDC, view_mat, z_buffer, tmp_drawing_view_mat);
		if (tmp_model->getShouldBoundingBox() )
		{
			vector<MyPolygon> bounding_box_polygon_list = tmp_model->getBoundingBoxPolygons();
			drawPolygons(*tmp_model, bounding_box_polygon_list, tmp_model->getBoundingBoxColor(), all_trans, pDC, view_mat, z_buffer, tmp_drawing_view_mat);
		}
		if (paint_vertex_normals) {
			if(show_original_normals)
				drawLines(pDC, tmp_model->getOriginalVertexNormalList(), tmp_model->getNormalsColor(), all_trans, view_mat, tmp_drawing_view_mat);
			else
				drawLines(pDC, tmp_model->getCalculatedVertexNormalList(), tmp_model->getNormalsColor(), all_trans, view_mat, tmp_drawing_view_mat);
		}
		if (paint_polygon_normals) {
			if (show_original_normals)
				drawLines(pDC, tmp_model->getOriginalPolygonNormalList(), tmp_model->getNormalsColor(), all_trans, view_mat, tmp_drawing_view_mat);
			else
				drawLines(pDC, tmp_model->getCalculatedPolygonNormalList(), tmp_model->getNormalsColor(), all_trans, view_mat, tmp_drawing_view_mat);

		}
	}
	//pDC->GetCurrentBitmap()->SetBitmapBits(view_width * view_height * 4, viewMatrix);
}
void Scene::drawLines(CDC* pDC, vector<Line> lines, COLORREF _color, Matrix _transformation, int view_mat[], double tmp_drawing_view_mat[])
{
	for (auto line = lines.begin(); line != lines.end(); line++)
	{
		Line transformed_line = tranformLine(*line, _transformation);
		drawLine(pDC, transformed_line, _color, view_mat, tmp_drawing_view_mat);
	}
}

int Scene::getMinXOfPolygon(Matrix transformation, MyPolygon &polygon)
{
	int min_x = INT_MAX;
	vector<Line> line_list = polygon.getLines();
	for (auto line = line_list.begin(); line != line_list.end(); line++)
	{
		Line transformed_line = tranformLine(*line, transformation);
		Point point = transformed_line.getP1();
		if (point.getX() < min_x)
		{
			min_x = point.getX();
		}
	}
	return min_x;
}

int Scene::getMaxXOfPolygon(Matrix transformation, MyPolygon &polygon)
{
	int max_x = INT_MIN;
	vector<Line> line_list = polygon.getLines();
	for (auto line = line_list.begin(); line != line_list.end(); line++)
	{
		Line transformed_line = tranformLine(*line, transformation);
		Point point = transformed_line.getP1();
		if (point.getX() > max_x)
		{
			max_x = point.getX();
		}
	}
	return max_x;
}

int Scene::getMinYOfPolygon(Matrix transformation, MyPolygon &polygon)
{
	int min_y = INT_MAX;
	vector<Line> line_list = polygon.getLines();
	for (auto line = line_list.begin(); line != line_list.end(); line++)
	{
		Line transformed_line = tranformLine(*line, transformation);
		Point point = transformed_line.getP1();
		if (point.getY() < min_y)
		{
			min_y = point.getY();
		}
	}
	return min_y;
}
int Scene::getMaxYOfPolygon(Matrix transformation, MyPolygon &polygon)
{
	int max_y = INT_MIN;
	vector<Line> line_list = polygon.getLines();
	for (auto line = line_list.begin(); line != line_list.end(); line++)
	{
		Line transformed_line = tranformLine(*line, transformation);
		Point point = transformed_line.getP1();
		if (point.getY() > max_y)
		{
			max_y = point.getY();
		}
	}
	return max_y;
}

void Scene::drawPolygons(Model model, vector<MyPolygon> polygon_list, COLORREF color, Matrix transformation, CDC* pDC, int view_mat[], double z_buffer[], double tmp_drawing_view_mat[])
{
	int count = 0;
	for (auto polygon = polygon_list.begin(); polygon != polygon_list.end(); polygon++)
	{
		count++;
		int min_x = getMinXOfPolygon(transformation, *polygon);
		int min_y = getMinYOfPolygon(transformation, *polygon);
		int max_x = getMaxXOfPolygon(transformation, *polygon);
		int max_y = getMaxYOfPolygon(transformation, *polygon);
			
		// draw edges of polygon
		vector<Line> line_list = polygon->getLines();
		if (count>-1) {
			for (auto line = line_list.begin(); line != line_list.end(); line++)
			{
				Line transformed_line = tranformLine(*line, transformation);
				if (abs(transformed_line.getP1().getY() - transformed_line.getP2().getY()) >= 1)
				{
					this->drawLineForScanConversion(pDC, transformed_line, tmp_drawing_view_mat);
				}
				//this->drawLine(pDC, transformed_line, RGB(255, 0, 0), view_mat, tmp_drawing_view_mat);
			}
		}
		// fill shape of polygon
		//if (count > 20 && count < 30 )
		if (count != -1)
			fillPolygon(model, *polygon, color, transformation, pDC, view_mat, z_buffer, tmp_drawing_view_mat);

		// clear last polygon from tmp drawing matrix
		for (int i = max(min_x - 2, 0); i < min(max_x + 2, width); i++)
		{
			for (int j = max(min_y - 2, 0); j < min(max_y + 2, height); j++)
			{
				tmp_drawing_view_mat[j*width + i] = 0;
			}
		}
	}
}

void Scene::fillPolygon(Model &model, MyPolygon polygon, COLORREF color, Matrix transformation, CDC* pDC, int view_mat[], double z_buffer[], double tmp_drawing_view_mat[])
{
	int min_x = getMinXOfPolygon(transformation, polygon);
	int min_y = getMinYOfPolygon(transformation, polygon);
	int max_x = getMaxXOfPolygon(transformation, polygon);
	int max_y = getMaxYOfPolygon(transformation, polygon);
	bool isInside = false;
	int lineThickness = 0;

	for (int y = max(min_y-2, 0); y <= min(max_y+2, height-1); y++)
	{
		// get the max x for this y
		int max_x_for_this_y = max_x;
		while (max_x_for_this_y > min_x && tmp_drawing_view_mat[y * width + max_x_for_this_y] == EMPTY_TMP_DRAWING_VIEW_MAT_PIXEL)
		{
			max_x_for_this_y--;
		}
		// get the min x for this y
		int min_x_for_this_y = min_x;
		while (min_x_for_this_y < max_x && tmp_drawing_view_mat[y * width + min_x_for_this_y] == EMPTY_TMP_DRAWING_VIEW_MAT_PIXEL)
		{
			min_x_for_this_y++;
		}
		// set borders of z for interpulation
		double max_z = tmp_drawing_view_mat[y * width + max_x_for_this_y];
		double min_z = tmp_drawing_view_mat[y * width + min_x_for_this_y];
		double dz = max_z - min_z;
		int dx = max_x_for_this_y - min_x_for_this_y;
		double slope = (dx == 0) ? 0 : (dz / dx);

		lineThickness = 0;
		isInside = false;
		double z = min_z;
		for (int x = max(min_x - 2, 0); x <= min(max_x_for_this_y + 2, width-1); x++)
		{			
			bool isLine = tmp_drawing_view_mat[y * width + x] != EMPTY_TMP_DRAWING_VIEW_MAT_PIXEL;

			if (isLine)
			{
				lineThickness++;
			}
			else if (lineThickness > 0) {
				isInside = !isInside;
				lineThickness = 0;
			}
			if (isInside || isLine)
			{
				//view_mat[y * width + x] = RGB(255, 0, 0);
				///*
				if (z_buffer[y * width + x] > z)
				{
					view_mat[y * width + x] = getColorAt(model, polygon, x, y, z);
					z_buffer[y * width + x] = z;
				}
				z += slope;
				//*/
				//view_mat[y * width + x] = getColorAt(model, polygon, x, y, z);
				//z += slope;
			}
		}
	}
}

COLORREF Scene::getColorAt(Model &model, MyPolygon polygon, int x, int y, double z)
{
	if (shadingType == FLAT_SHADING)
	{
		return getFlatColorAt(model, polygon, x, y);
	}
	else if (shadingType == GOURAUD_SHADING)
	{
		return getGouraudColorAt(model, polygon, x, y);
	}
	else if (shadingType == PHONG_SHADING)
	{
		return getPhongColorAt(model, polygon, x, y);
	}
}

COLORREF Scene::getFlatColorAt(Model &model, MyPolygon polygon, int x, int y)
{
	Point objectLocation = Point(x, y, 1);
	LightCoefficient k_d = LightCoefficient(1, 1, 1);
	COLORREF color = k_a * I_a;
	for (int i = 0; i < MAX_COUNT_OF_LIGHTSOURCES; i++)
	{
		if (lightSources[i] == NULL)
		{
			continue;
		}
		Vector L = lightSources[i]->getNormal(objectLocation);
		LightCoefficient I_p = lightSources[i]->getI_p(objectLocation);
		Vector N = polygon.getOriginalNormal();
		double normalSize = sqrt(pow(N[0], 2) + pow(N[1], 2) + pow(N[2], 2));
		N[0] = N[0] / normalSize;
		N[1] = N[1] / normalSize;
		N[2] = N[2] / normalSize;
		color += I_p * k_d * (L * N);	
	}
	return color;
}

COLORREF Scene::getGouraudColorAt(Model &model, MyPolygon polygon, int x, int y)
{
	return k_a * I_a;
}

COLORREF Scene::getPhongColorAt(Model &model, MyPolygon polygon, int x, int y)
{
	return k_a * I_a;
}

Matrix Scene::strechToScreenSize(CRect r)
{
	width = abs(r.right - r.left);
	height = abs(r.bottom - r.top);
	
	double min_axis;
	if ((width / 2) < (height / 2))
		min_axis = (width / 2);
	else
		min_axis = (height / 2);

	return Matrix(Vector(min_axis, 0, 0, width / 2),
				  Vector(0, min_axis, 0, height / 2),
				  Vector(0, 0, min_axis, 0),
				  Vector(0, 0, 0, 1));
	

}

void Scene::drawLineForScanConversion(CDC* pDC, Line line, double depth_mat[]) 
{
	Point p1 = line.getP1();
	Point p2 = line.getP2();
	double dy, dx, dz, slope, zSlope;
	int x, y;
	double z;
	int n = 0;

	// p2.y should be bigger the p1.y
	if (p1.getY() > p2.getY())
	{
		Point tmp_p = p1;
		p1 = p2;
		p2 = tmp_p;
	}

	//set dx and dy
	dy = (p2.getY() - p1.getY());
	dx = (p2.getX() - p1.getX());
	dz = (p2.getZ() - p1.getZ());
	slope = dx / dy;
	zSlope = dz / dy;

	//init x and y
	x = p1.getX();
	y = p1.getY();
	z = p1.getZ();

	while (y < int(p2.getY()))
	{		
		if (y >= 0 && y < height && x >= 0 && x + int(n * slope) < width)
		{
			depth_mat[int(y * width + x + n * slope)] = z;
		}
		y = y + 1;
		z += zSlope;
		n++;
	}
}

void Scene::drawLine(CDC* pDC, Line line, COLORREF _color, int view_mat[], double depth_mat[]) {
	
	COLORREF color = _color;
	Point p1 = line.getP1();
	Point p2 = line.getP2();
	Point tmp_p;
	double dy, dx, dz, d, d_e, d_ne;
	int x, y, z;
	int tmp_x, tmp_y, tmp_z;

	int opposite = 1;
	bool slope_too_big = false;
	bool slope_negative = false;


	//set dx and dy
	dy = (p2.getY() - p1.getY());
	dx = (p2.getX() - p1.getX());
	dz = (p2.getZ() - p1.getZ());

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
		dz = (p2.getZ() - p1.getZ());


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
		dz = (p2.getZ() - p1.getZ());
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
	z = p1.getZ();

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
		tmp_z = z;

		if (slope_negative == true)
		{
			tmp_y = int(2 * p1.getY() - tmp_y);
		}


		//slope is too big
		/*
		if( slope_too_big == false )
			pDC->SetPixel(tmp_x, tmp_y, color);
		else
			pDC->SetPixel(tmp_y, tmp_x, color);
		*/
		int tmp_color = 0;
		tmp_color = (GetBValue(color)) + (GetRValue(color) << 16) + (GetGValue(color) << 8);

		if (slope_too_big == false)
		{

			if ((tmp_y >= 0) && (tmp_y < height) && (tmp_x >= 0) && (tmp_x < width))
			{
				//view_mat[tmp_x * width + tmp_y] = tmp_color;
				view_mat[tmp_y * width + tmp_x] = tmp_color;
				//depth_mat[tmp_y * width + tmp_x] = 1; // tmp_z;
			}
		}

		else {
			if ((tmp_y >= 0) && (tmp_y < width) && (tmp_x >= 0) && (tmp_x < height))
			{
				//view_mat[tmp_y * width + tmp_x] = tmp_color;
				view_mat[tmp_x * width + tmp_y] = tmp_color;
				//depth_mat[tmp_x * width + tmp_y] = 1; // tmp_z;
			}
		}
			
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

void Scene::updateTransformationViewSpaceMatricesOfObjectAtIndex(Matrix _transformationMatrix, int _index)
{
	if (_index >= model_list.size() || _index < 0)
	{
		return;
	}
	model_list[_index].transformInViewSpace(_transformationMatrix);
}
void Scene::updateTransformationObjectSpaceMatricesOfObjectAtIndex(Matrix _transformationMatrix, int _index)
{
	if (_index >= model_list.size() || _index < 0)
	{
		return;
	}
	model_list[_index].transformInObjectSpace(_transformationMatrix);
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

void Scene::setColorOfAllModels(COLORREF color) 
{
	modelsColor = color;
	isModelColorSet = true;
	for (int i = 0; i < model_list.size(); i++)
	{
		model_list[i].setColor(color);
	}
}

void Scene::setBoundingBoxColor(COLORREF color)
{
	boundingBoxColor = color;
	for (int i = 0; i < model_list.size(); i++)
	{
		model_list[i].setBoundingBoxColor(color);
	}
}

void Scene::setNormalsColor(COLORREF color)
{
	normalsColor = color;
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

void Scene::showOriginalNormals(bool _show_original_normals)
{
	show_original_normals = _show_original_normals;
}

void Scene::setIsPerspective(bool _isPerspective)
{
	isPerspective = _isPerspective;
}

void Scene::setAlpha(double _alpha)
{
	alpha = _alpha;
}

void Scene::setD(double _d)
{
	d = _d;
}

Matrix Scene::getTransformationMatrix(Model tmp_model, int camera_number, CRect r)
{
	//Matrix tmp_camera_trans = camera_list[camera_number].getTransformation();
	Matrix tmp_model_trans = tmp_model.getTransformationMatrix();

	Matrix all_trans;
	if (isPerspective)
	{
		Matrix perspectiveTransformation = Transformations::prespective(alpha, d);
		//all_trans = tmp_camera_trans * tmp_model_trans * perspectiveTransformation * strechToScreenSize(r);
		all_trans = tmp_model_trans * perspectiveTransformation * strechToScreenSize(r);
	}
	else
	{
		all_trans = tmp_model_trans * strechToScreenSize(r);

	}
	return all_trans;
}

int Scene::getNumberOfModels()
{
	return model_list.size();
}
