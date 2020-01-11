#include "Scene.h"
#include "MyPolygon.h"
#include "Transformations.h"
#include "ParallelLightSource.h"
#include "PointLightSource.h"
#include "CGWorkDefines.h"
#include <algorithm>  
#include "SpotLightSource.h"
#include "antiAliasing.h"

Scene::Scene()
{
	show_background = false;
	tile_background = true;
	show_regular_normals = true;
	paint_bounding_box = false;
	show_original_normals = true;
	show_positive_normals = false;
	//ParallelLightSource *parallelLightSource = new ParallelLightSource(Vector(1, 0, 0, 0), LightCoefficient(1, 1, 1));
	//PointLightSource *parallelLightSource = new PointLightSource(Point(1, 0, 0), LightCoefficient(255, 255, 255));
	//SpotLightSource *spot_light_source = new SpotLightSource(Point(400, 100, 0),Vector(1,0,0,0), LightCoefficient(255, 255, 255));

	//lightSources[0] = (spot_light_source);

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

void Scene::setSpecularityExponent(int n) {
	specularityExponent = n;
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

 void Scene::highlightModel(int modelIndex)
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

void Scene::setColorOfModelAtIndex(COLORREF _color, int modelIndex)
{
	unHighlightModel();
	model_list[modelIndex].setColor(_color);
	highlightModel(modelIndex);
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

void Scene::Draw(CDC* pDC, int camera_number, CRect r, int view_mat[], double tmp_drawing_view_mat[], COLORREF background_color) {
	width = abs(r.right - r.left);
	height = abs(r.bottom - r.top);
	vector<double> *z_buffer = new vector<double>[height*width];
	vector<LightCoefficient> *tmp_view_mat = new vector<LightCoefficient>[height*width];
	for (int i = 0; i < height*width; i++)
	{
		z_buffer[i].clear();
		z_buffer[i].push_back(EMPTY_Z_BUFFER_PIXEL);
	}

	if (show_background)
	{
		drawBackground(tmp_view_mat, view_mat);
	}
	else
	{
		for (int i = 0; i < height*width; i++)
		{
			//(GetBValue(background_color)) + (GetRValue(background_color) << 16) + (GetGValue(background_color) << 8)
			LightCoefficient tmp_color(GetRValue(background_color), GetGValue(background_color), GetBValue(background_color));
			tmp_color.setAlpha(1);
			tmp_color.setActive(true);
			tmp_view_mat[i].push_back(tmp_color);
		}
	}

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
		drawPolygons(*tmp_model, model_polygon_list, all_trans, pDC, view_mat, z_buffer, tmp_view_mat, tmp_drawing_view_mat);
		if (tmp_model->getShouldBoundingBox() )
		{
			vector<MyPolygon> bounding_box_polygon_list = tmp_model->getBoundingBoxPolygons();
			drawPolygons(*tmp_model, bounding_box_polygon_list, all_trans, pDC, view_mat, z_buffer, tmp_view_mat, tmp_drawing_view_mat);
		}
		if (paint_vertex_normals) {
			if (show_original_normals)
			{
				drawLines(pDC, tmp_model->getOriginalVertexNormalList(show_regular_normals), tmp_model->getNormalsColor(), all_trans, view_mat, tmp_drawing_view_mat);
			}
			else
			{
				drawLines(pDC, tmp_model->getCalculatedVertexNormalList(show_regular_normals), tmp_model->getNormalsColor(), all_trans, view_mat, tmp_drawing_view_mat);
			}
		}
		if (paint_polygon_normals) {
			if (show_original_normals)
			{
				drawLines(pDC, tmp_model->getOriginalPolygonNormalList(show_regular_normals), tmp_model->getNormalsColor(), all_trans, view_mat, tmp_drawing_view_mat);
			}
			else
				drawLines(pDC, tmp_model->getCalculatedPolygonNormalList(show_regular_normals), tmp_model->getNormalsColor(), all_trans, view_mat, tmp_drawing_view_mat);

		}
		if (drawSilhouette) {
			drawLines(pDC, tmp_model->getSilhouetteLinesList(all_trans), silhouetteColor, all_trans, view_mat, tmp_drawing_view_mat);
		}
	}

	if (!draw_wireFrame)
	{


		//transperancy calculation
		for (int i = 0; i < height*width; i++)
		{
			double fog_intensity = 1;
			if (tmp_view_mat[i][0].isActive())
			{
				tmp_view_mat[i][0] = flattenAlpha(tmp_view_mat[i], z_buffer[i], there_is_no_fog, fog_intensity);
			}
		}

		//find max
		int max = 1;
		for (int i = 0; i < height*width; i++)
		{
			int tmp_max = 0;
			if (tmp_view_mat[i][0].isActive())
			{
				tmp_max = max(max(tmp_view_mat[i][0].getR(), tmp_view_mat[i][0].getG()), tmp_view_mat[i][0].getB());
				if (tmp_max > max)
					max = tmp_max;
			}
		}


		double normalize_factor = (max > 255) ? (255 / double(max)) : 1;
		//normalize + fill view_mat
		for (int i = 0; i < height*width; i++)
		{
			//if (tmp_view_mat[i][0].isActive())
			{
				tmp_view_mat[i][0] = tmp_view_mat[i][0].multiplyColorOnly(normalize_factor);
				double partion = z_buffer[i][0] > 0 ? z_buffer[i][0] : 0;
				//partion = (4 / (1 + pow(1.0001, -partion))) - 2;
				
				partion = (40 * partion / EMPTY_Z_BUFFER_PIXEL);
				partion = partion <= 1 ? partion : 1;
				if (there_is_no_fog)
					partion = 0;
				tmp_view_mat[i][0] = tmp_view_mat[i][0].multiplyColorOnly(1 - partion) + tmp_view_mat[i][0].getFog() * partion;
				tmp_view_mat[i][0] = tmp_view_mat[i][0] + tmp_view_mat[i][0].getShine();
				

				double R = tmp_view_mat[i][0].getR() > 255 ? 255 : tmp_view_mat[i][0].getR();
				double G = tmp_view_mat[i][0].getG() > 255 ? 255 : tmp_view_mat[i][0].getG();
				double B = tmp_view_mat[i][0].getB() > 255 ? 255 : tmp_view_mat[i][0].getB();
				COLORREF tmp_color = RGB(R, G, B);

				view_mat[i] = ((GetBValue(tmp_color)) + (GetRValue(tmp_color) << 16) + (GetGValue(tmp_color) << 8));
			}
		}
	}
	if(shouldFilter)
		antiAliasing::blur(view_mat, width, height, kernal_size, kernal_type);

	//pDC->GetCurrentBitmap()->SetBitmapBits(view_width * view_height * 4, viewMatrix);
	delete[] z_buffer;
	delete[] tmp_view_mat;
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

void Scene::drawPolygons(Model model, vector<MyPolygon> polygon_list, Matrix transformation, CDC* pDC, int view_mat[], vector<double> z_buffer[], vector<LightCoefficient> tmp_view_mat[], double tmp_drawing_view_mat[])
{
	LightCoefficient *color_mat = new LightCoefficient[height*width];
	Vector* normal_mat = new Vector[height*width];
	int count = 0;
	for (auto polygon = polygon_list.begin(); polygon != polygon_list.end(); polygon++)
	{
		count++;
		int min_x = getMinXOfPolygon(transformation, *polygon);
		int min_y = getMinYOfPolygon(transformation, *polygon);
		int max_x = getMaxXOfPolygon(transformation, *polygon);
		int max_y = getMaxYOfPolygon(transformation, *polygon);

		//if all the polgon is out of the screen
		if (max_x < 0 || min_x >= width || max_y < 0 || min_y >= height)
		{
			continue;
		}

		// draw edges of polygon
		MyPolygon transformedPolygon = polygon->tranformPolygon(transformation);

		Vector Z(0, 0, 1, 0);
		Vector N = transformedPolygon.getOriginalNormal(true);
		double normal_dot_z = Z * N;
		if (show_positive_normals == false || (show_positive_normals && normal_dot_z > 0))
		{

			vector<Line> line_list = transformedPolygon.getLines();
			//if ((count == 50 || count == 51)) {
			if (count != -1) {
				for (auto transformed_line = line_list.begin(); transformed_line != line_list.end(); transformed_line++)
				{
					//Line transformed_line = tranformLine(*line, transformation);
					if (!draw_wireFrame)
					{
						if (abs(transformed_line->getP1().getY() - transformed_line->getP2().getY()) >= 1)
						{
							this->drawLineForScanConversion(pDC, *transformed_line, tmp_drawing_view_mat, normal_mat, color_mat, model, transformedPolygon);
						}
					}
					else
					{
						this->drawLine(pDC, *transformed_line, model.getModelColor(), view_mat, tmp_drawing_view_mat);
					}
				}
			}



			// fill shape of polygon
			//if ((count == 50 ||count == 51) && !draw_wireFrame)
			if (count != -1 && !draw_wireFrame)
				fillPolygon(model, *polygon, transformation, pDC, tmp_view_mat, z_buffer, tmp_drawing_view_mat, normal_mat, color_mat);

			// clear last polygon from tmp drawing matrix
			if (!draw_wireFrame)
			{
				for (int i = max(min_x - 2, 0); i < min(max_x + 2, width); i++)
				{
					for (int j = max(min_y - 2, 0); j < min(max_y + 2, height); j++)
					{
						tmp_drawing_view_mat[j*width + i] = EMPTY_TMP_DRAWING_VIEW_MAT_PIXEL;
					}
				}
			}
			//if (count == 2)
			//	break;
		}
	}
	delete[] color_mat;
	delete[] normal_mat;
}

void Scene::fillPolygon(Model &model, MyPolygon polygon, Matrix transformation, CDC* pDC, vector<LightCoefficient> view_mat[], vector<double> z_buffer[], double tmp_drawing_view_mat[], Vector* normal_mat, LightCoefficient color_mat[])
{   
	bool color_from_edge = false;
	if (shadingType == FLAT_SHADING || shadingType == GOURAUD_SHADING)
	{
		color_from_edge = true;
	}

	int min_x = getMinXOfPolygon(transformation, polygon);
	int min_y = getMinYOfPolygon(transformation, polygon);
	int max_x = getMaxXOfPolygon(transformation, polygon);
	int max_y = getMaxYOfPolygon(transformation, polygon);

	//if all the polgon is out of the screen
	if (max_x < 0 || min_x >= width || max_y < 0 || min_y >= height)
	{
		return;
	}

	//limit the max to the screen
	min_x = max(min_x - 2, 0);
	int real_min_y = min_y;
	min_y = max(min_y - 2, 0);
	max_x = min(max_x + 2, width - 1);
	max_y = min(max_y + 2, height - 1);

	bool isInside = false;
	int lineThickness = 0;

	for (int y = max(min_y, 0); y <= min(max_y, height-1); y++)
	{
		// get the max x for this y
		int max_x_for_this_y = max_x;
		while ((max_x_for_this_y > min_x) && (tmp_drawing_view_mat[y * width + max_x_for_this_y] == EMPTY_TMP_DRAWING_VIEW_MAT_PIXEL))
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


		for (int x = max(min_x_for_this_y - 2, 0); x <= min(max_x_for_this_y + 2, width-1); x++)
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
			if ((isInside || (isLine && x > (min_x_for_this_y))) && y > real_min_y)
			//if (isInside)
			{
				double min_factor = 0.5;
				if ((max_x_for_this_y - min_x_for_this_y) > 0)
				{
					min_factor = ((double)(max_x_for_this_y - x)) / (max_x_for_this_y - min_x_for_this_y);
				}
				double max_factor = 1 - min_factor;

				LightCoefficient tmp_color;
				if (color_from_edge == true)
				{
					tmp_color = color_mat[y * width + min_x_for_this_y] * min_factor + color_mat[y * width + max_x_for_this_y] * max_factor;
				}
				else
				{
					Vector N1 = normal_mat[y * width + min_x_for_this_y];
					Vector N2 = normal_mat[y * width + max_x_for_this_y];
					int steps = max_x_for_this_y - min_x_for_this_y;
					int dx = x - min_x_for_this_y;

					Vector tmp_N = Transformations::getNormalInTheMiddle(N1, N2, steps, dx);
					tmp_color = getColorAtPoint(model, polygon, x, y, z, tmp_N);
				}

				tmp_color.setActive(true);
				view_mat[y * width + x].push_back(tmp_color);
				z_buffer[y * width + x].push_back(z);
			}
			z += slope;
		}
	}
}

LightCoefficient Scene::flattenAlpha(vector<LightCoefficient> allColors, vector<double> &z_buffer, bool _there_is_no_fog, double _fog_intensity)
{
	
	// Declaring vector of pairs 
	vector< pair <double, int> > vect;

	// Initializing 1st and 2nd element of 
	// pairs with array values 

	int n = z_buffer.size();

	// Entering values in vector of pairs 
	for (int i = 0; i < n; i++) {
		vect.push_back(make_pair(z_buffer[i], i));
	}

	sort(vect.begin(), vect.end());

	double alpha = 1 , alpha_tmp;
	LightCoefficient color(0,0,0);
	alpha = 1;

	for (int i = 0 ; i < n; i++) 
	{
		LightCoefficient new_color = getFogColor(allColors[vect[i].second], vect[i].first, _there_is_no_fog, _fog_intensity);
		alpha_tmp = new_color.getAlpha();
		color = color + new_color * alpha * alpha_tmp;	
		alpha = alpha * (1 - alpha_tmp);
	}
	z_buffer[0] = vect[0].first;
	color.setActive(true);
	return color;
}


LightCoefficient Scene::getColorAtPoint(Model &model, MyPolygon polygon, int x, int y, double z, Vector N)
{

	Point objectLocation = Point(x, y, z);
	LightCoefficient k_d = LightCoefficient(GetRValue(model.getModelColor()), GetGValue(model.getModelColor()), GetBValue(model.getModelColor()), model.getAlpha());
	k_a = k_d;
	LightCoefficient color = k_a * I_a;
	for (int i = 0; i < MAX_COUNT_OF_LIGHTSOURCES; i++)
	{
		if (lightSources[i] == NULL)
		{
			continue;
		}
		Vector L = lightSources[i]->getNormal(objectLocation);
		
		//if the L vector is zero then we dont see the light
		// it means that this is a spot light and we dont see it
		if( L[0] != 0 || L[1] != 0 || L[2] != 0 || L[3] != 0)
		{
			LightCoefficient I_p = lightSources[i]->getI_p(objectLocation);
			Vector flip_L = lightSources[i]->getFlipNormal(objectLocation);
			if (N * flip_L > 0)
			{
				//Vector flip_L = Transformations::flipNormal(L);
				Vector flip_L = lightSources[i]->getFlipNormal(objectLocation);
				flip_L.Normalize();
				Vector tmp_vec = Transformations::getNormalInTheMiddle(flip_L, N, 1, 2);
				tmp_vec.Normalize();
				V.Normalize();
				double shine_factor = V * tmp_vec;
				shine_factor = shine_factor > 0 ? shine_factor : 0;

				LightCoefficient tmp = k_s * pow(shine_factor, specularityExponent);

				color = color + (I_p * (((double)1)/255) * k_d * (abs(L * N)));
				LightCoefficient tmp_shine = color.getShine();
				color.setShine(tmp_shine.getR() + tmp.getR(), tmp_shine.getG() + tmp.getG(), tmp_shine.getB() + tmp.getB());
			}
		}
		color.setActive(true);
	}
	color.setAlpha(model.getAlpha());
	return color;
}


LightCoefficient Scene::getGouraudColorAt(Model &model, MyPolygon polygon, int x, int y, double z)
{
	return (k_a * I_a);
}

COLORREF Scene::getPhongColorAt(Model &model, MyPolygon polygon, int x, int y)
{
	return (k_a * I_a).LightCoefficientToRGB();
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

void Scene::drawLineForScanConversion(CDC* pDC, Line line, double depth_mat[], Vector* normal_mat, LightCoefficient *color_mat, Model &model, MyPolygon &polygon)
{
	Point p1 = line.getP1();
	Point p2 = line.getP2();
	double dy, dx, dz, slope, zSlope;

	LightCoefficient dcolor, colorSlope;
	Vector dnormal, normalSlope;
	
	int y;
	int x;
	int clipedX, clipedY;
	double z;
	LightCoefficient color;
	

	// p2.y should be bigger the p1.y
	if (p1.getY() > p2.getY())
	{
		Point tmp_p = p1;
		p1 = p2;
		p2 = tmp_p;
	}

	//set dx and dy
	dy = (int(p2.getY()) - int(p1.getY()));
	dx = (int(p2.getX()) - int(p1.getX()));
	dz = (p2.getZ() - p1.getZ());

	Vector N1 = p1.getOriginalNormal(show_regular_normals);
	Vector N2 = p2.getOriginalNormal(show_regular_normals);

	dnormal = (N2 - N1);

	LightCoefficient c1 = getColorAtPoint(model, polygon, p2.getX(), p2.getY(), p2.getZ(), N2);
	LightCoefficient c2 = getColorAtPoint(model, polygon, p1.getX(), p1.getY(), p1.getZ(), N1);
	dcolor = (c1 + c2 * (-1));

	slope = dx / dy;
	zSlope = dz / dy;
	colorSlope = dcolor * (1 / ((double)dy));

	//init x and y
	x = p1.getX();
	y = p1.getY();
	z = p1.getZ();
	color = getColorAtPoint(model, polygon, p1.getX(), p1.getY(), p1.getZ(), N1);
	

	int n = 0;
	LightCoefficient polygonColor = getColorAtPoint(model, polygon, polygon.getCenter().getX(), polygon.getCenter().getY(), polygon.getCenter().getZ(), polygon.getOriginalNormal(show_regular_normals));

	while (y <= int(p2.getY()))
	{
		//keep y in screen
		clipedY = y < 0 ? 0 : y;
		clipedY = clipedY >= height ? height - 1 : clipedY;

		//keep x in screen
		clipedX = x + round(n * slope);
		clipedX = clipedX < 0 ? 0 : clipedX;
		clipedX = clipedX >= width ? width - 1 : clipedX;
		/*
		if (clipedY >= 0 && clipedY < height && clipedX >= 0 && clipedX < width)
		{
			depth_mat[int(clipedY * width + clipedX)] = z;
			draw_mat[int(clipedY * width + clipedX)] = 1;
		}*/
		depth_mat[int(clipedY * width + clipedX)] = z;
		//draw_mat[int(clipedY * width + clipedX)] = 1;
		if (shadingType == FLAT_SHADING)
		{
			color_mat[int(clipedY * width + clipedX)] = polygonColor;
		}
		else if (shadingType == GOURAUD_SHADING)
		{
			color_mat[int(clipedY * width + clipedX)] = color;
			color = color + colorSlope;
		}
		else
		{
			Vector normal_vec = Transformations::getNormalInTheMiddle(N1, N2, dy, n);
			normal_mat[int(clipedY * width + clipedX)] = normal_vec;
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

void Scene::setFogColor(COLORREF color)
{
	fog_color = color;
}

void Scene::setSilhouetteColor(COLORREF color)
{
	silhouetteColor = color;
}

bool Scene::getDrawSilhouette()
{
	return drawSilhouette;
}

void Scene::setDrawSilhouette(bool _drawSilhouette)
{
	drawSilhouette = _drawSilhouette;
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

void Scene::drawWireFrame(bool _draw_wireFrame)
{
	draw_wireFrame = _draw_wireFrame;
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

void Scene::setAmbientLight(LightParams m_ambientLight)
{
	I_a = LightCoefficient(m_ambientLight.colorR/255.0, m_ambientLight.colorG/255.0, m_ambientLight.colorB/255.0);
}

void Scene::setLightSourceWithParams(int idx, LightParams lightParams)
{
	if (lightSources[idx] != NULL) {
		delete lightSources[idx];
	}
	if (lightParams.enabled)
	{
		LightCoefficient I_p(lightParams.colorR, lightParams.colorG, lightParams.colorB);
		if (lightParams.type == LIGHT_TYPE_DIRECTIONAL)
		{
			Vector direction(lightParams.dirX, lightParams.dirY, lightParams.dirZ, 0);
			lightSources[idx] = new ParallelLightSource(direction, I_p);
		}
		else if (lightParams.type == LIGHT_TYPE_POINT)
		{
			Point position(lightParams.posX, lightParams.posY, lightParams.posZ);
			lightSources[idx] = new PointLightSource(position, I_p);
		}
		else 
		{
			Point position(lightParams.posX, lightParams.posY, lightParams.posZ);
			Vector direction(lightParams.dirX, lightParams.dirY, lightParams.dirZ, 0);
			lightSources[idx] = new SpotLightSource(position, direction, I_p);
		}
	}
	else
	{
		lightSources[idx] = NULL;
	}
}

void Scene::setShadingType(shadingTypes _shadingType)
{
	shadingType = _shadingType;
}

bool Scene::getRegularNormals()
{
	return show_regular_normals;
}

void Scene::setRegularNormals(bool _show_regular_normals)
{
	show_regular_normals = _show_regular_normals;
}

bool Scene::getUseBackgroundImage()
{
	return show_background;
}
void Scene::setUseBackgroundImage(bool _useBackGroundImage)
{
	show_background = _useBackGroundImage;
}

bool Scene::getTileBackgroundImage()
{
	return tile_background;
}
void Scene::setTileBackgroundImage(bool _tileBackGroungImage) {
	tile_background = _tileBackGroungImage;
}


void Scene::setBackgroundImageHeight(int _height)
{
	background_image_height = _height;
}
void Scene::setBackgroungImageWidth(int _width)
{
	background_image_width = _width;
}
void Scene::setBackgroundImage(vector<COLORREF> _image)
{
	background_image = _image;
}

void Scene::drawBackground(vector<LightCoefficient> *tmp_view_mat, int view_mat[])
{
	if (tile_background)
		drawBackgroundTile(tmp_view_mat, view_mat);
	else
		drawBackgroundStretch(tmp_view_mat, view_mat);
}

void Scene::drawBackgroundTile(vector<LightCoefficient> tmp_view_mat[], int view_mat[])
{
	/*
			for (int i = 0; i < height*width; i++)
		{
			//(GetBValue(background_color)) + (GetRValue(background_color) << 16) + (GetGValue(background_color) << 8)
			LightCoefficient tmp_color(GetRValue(background_color), GetGValue(background_color), GetBValue(background_color));
			tmp_color.setActive(true);
			tmp_view_mat[i].push_back(tmp_color);
		}
	*/
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int tmp_i = i % background_image_height;
			int tmp_j = j % background_image_width;
			COLORREF background_color = background_image[tmp_i * background_image_width + tmp_j];
			view_mat[i * width + j] = background_color;
			LightCoefficient background_lightCoefficient(GetBValue(background_color), GetGValue(background_color), GetRValue(background_color));
			background_lightCoefficient.setActive(true);
			tmp_view_mat[i * width + j].push_back(background_lightCoefficient);
		}
	}


}

void Scene::drawBackgroundStretch(vector<LightCoefficient> *tmp_view_mat, int view_mat[])
{
	double d_i = 0, d_j = 0;
	double d_i_friction = double(background_image_height) / height;
	double d_j_friction = double(background_image_width) / width;

	for (int i = 0; i < height; i++)
	{
		d_j = 0;
		for (int j = 0; j < width; j++)
		{
			int tmp_i = i % background_image_height;
			int tmp_j = j % background_image_width;
			COLORREF background_color = background_image[int(d_i) * background_image_width + int(d_j)];
			view_mat[i * width + j] = background_color;
			LightCoefficient background_lightCoefficient(GetRValue(background_color), GetGValue(background_color), GetBValue(background_color), 1.0);
			//LightCoefficient background_lightCoefficient(0, 0, 0);
			background_lightCoefficient.setActive(true);
			tmp_view_mat[i * width + j].push_back(background_lightCoefficient);
			d_j = d_j + d_j_friction;
		}
		d_i = d_i + d_i_friction;
	}
}

void Scene::setShowPositiveNormals(bool _show_positive_normals)
{
	show_positive_normals = _show_positive_normals;
}


bool Scene::getShowPositiveNormals()
{
	return show_positive_normals;
}

int Scene::getSpecularityExponent()
{
	return specularityExponent;
}

void Scene::setAlphaOfAllModels(double _alpha)
{
	for (int i = 0; i < model_list.size(); i++)
	{
		model_list[i].setAlpha(_alpha);
	}
}

void Scene::setAlphaOfModelAtIndex(double alpha, int modelIndex)
{
	model_list[modelIndex].setAlpha(alpha);
}


LightCoefficient Scene::getFogColor(LightCoefficient &_color, double z, bool _there_is_no_fog, double _fog_intensity)
{
	if (_there_is_no_fog)
	{
		return _color;
	}
	else
	{
		double fog_added_value = 0;
		double mul_factor = _fog_intensity * z;
		/*
		if(mul_factor > 255)
			fog_added_value = 255;
		else if(mul_factor < 0)
			fog_added_value = 0;
		else
			fog_added_value = mul_factor;
		fog_added_value = fog_added_value / 255;
		*/
		fog_added_value = 1;
		_color.setFog(GetRValue(fog_color)*fog_added_value, GetGValue(fog_color)*fog_added_value, GetBValue(fog_color)*fog_added_value);

		return _color;
	}
}


bool Scene::getShowFog() 
{
	return !there_is_no_fog;
}

void Scene::setShowFog(bool _show_fog)
{
	there_is_no_fog = !_show_fog;
}

void Scene::setShouldPerformAntiAliasing(bool _shouldPerformAntiAliasing)
{
	shouldFilter = _shouldPerformAntiAliasing;
}

bool Scene::getShouldPerformAntiAliasing()
{
	return shouldFilter;
}
