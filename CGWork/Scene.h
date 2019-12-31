#pragma once
#include <iostream>
#include <vector>

#include"Model.h"
#include"Camera.h"
#include "lightCoefficient.h"
#include "lightSource.h"
#include "Light.h"
#include "Vector.h"
#include "CGWorkDefines.h"

//for the CDC
#include "stdafx.h"

class Scene
{
public:
	Scene();
	~Scene();
	void addModel(Model _model);
	void AddCamera(Camera _camera);
	void Draw(CDC* pDC, int camera_number, CRect r, int view_mat[], double z_buffer[], double tmp_drawing_view_mat[]);
	void drawPolygons(Model model, vector<MyPolygon> polygon_list, Matrix transformation, CDC* pDC, int view_mat[], double z_buffer[], double tmp_drawing_view_mat[]);
	Matrix strechToScreenSize( CRect r);
	Line tranformLine(Line line, Matrix transformationMatrix);
	Point tranformPoint(Point p, Matrix transformationMatrix);
	void updateTransformationObjectSpaceMatricesOfAllObjects(Matrix transformationMatrix);
	void updateTransformationViewSpaceMatricesOfAllObjects(Matrix transformationMatrix);
	void updateTransformationMatrixOfCamera(Matrix transformationMatrix, bool isRotation);
	void setSouldShowBoundingBox(bool _show_bounding_box);
	void setColorOfAllModels(COLORREF color);
	void setBoundingBoxColor(COLORREF color);
	void setNormalsColor(COLORREF color);
	bool paint_vertex_normals = false;
	bool paint_polygon_normals = false;
	void showOriginalNormals(bool _show_original_normals);
	void setIsPerspective(bool _isPerspective);
	Matrix getTransformationMatrix(Model tmp_model, int camera_number, CRect r);
	void setAlpha(double _alpha);
	void setD(double _d);
	int getNumberOfModels();
	void updateTransformationViewSpaceMatricesOfObjectAtIndex(Matrix _transformationMatrix, int _index);
	void updateTransformationObjectSpaceMatricesOfObjectAtIndex(Matrix _transformationMatrix, int _index);
	void highlightModel(COLORREF _color, int modelIndex);
	COLORREF getModelColor();
	COLORREF getFaddedModelColor(int modelIndex);
	void unHighlightModel();
	void drawWireFrame(bool _draw_wireFrame);
	void setLightSourceWithParams(int idx, LightParams lightParams);
	void setAmbientLight(LightParams m_ambientLight);
	void setShadingType(shadingTypes _shadingType);
	void setSilhouetteColor(COLORREF color);
	bool getDrawSilhouette();
	void setDrawSilhouette(bool _drawSilhouette);
	bool getRegularNormals();
	void setRegularNormals(bool _show_regular_normals);
	bool getUseBackgroundImage(); 
	void setUseBackgroundImage(bool _show_background);
	bool getTileBackgroundImage();
	void setTileBackgroundImage(bool _tile_background);

	void setBackgroundImageHeight(int _height);
	void setBackgroungImageWidth(int _width);
	void setBackgroundImage(vector<COLORREF> _image);
	void drawBackground(int view_mat[]);
	void drawBackgroundTile(int view_mat[]);
	void drawBackgroundStretch(int view_mat[]);
	void setShowPositiveNormals(bool _show_positive_normals);
	bool getShowPositiveNormals();
	void setSpecularityExponent(int n);


private:
	int specularityExponent = 2;
	Vector V = Vector(0, 0, -1, 0);
	
	bool show_regular_normals;
	std::vector<Model> model_list;
	std::vector<Camera> camera_list;
	void Scene::drawLine(CDC* pDC, Line line, COLORREF _color, int view_mat[], double depth_mat[]);
	void drawLines(CDC* pDC, vector<Line> line, COLORREF _color, Matrix _transformation, int view_mat[], double tmp_drawing_view_mat[]);
	bool paint_bounding_box;
	COLORREF modelsColor;
	bool isModelColorSet = false;
	COLORREF boundingBoxColor = RGB(1, 0, 0);
	COLORREF normalsColor = RGB(0, 1, 0);
	void calcModelMinMax(Model &_model);
	void addBoundingBox(Model &_model);
	void normalizeTheModel(Model &_model);
	void setModelColor(Model &_model);
	int getSpecularityExponent();
	// scane conversion
	int getMinXOfPolygon(Matrix transformation, MyPolygon &polygon);
	int getMaxXOfPolygon(Matrix transformation, MyPolygon &polygon);
	int getMinYOfPolygon(Matrix transformation, MyPolygon &polygon);
	int getMaxYOfPolygon(Matrix transformation, MyPolygon &polygon);

	void fillPolygon(Model &model, MyPolygon polygon, Matrix transformation, CDC* pDC, LightCoefficient view_mat[], double z_buffer[], double tmp_drawing_view_mat[], Vector* normal_mat, LightCoefficient* color_mat);
	void drawLineForScanConversion(CDC* pDC, Line line, double depth_mat[], int draw_mat[], Vector* normal_mat, LightCoefficient* color_mat, Model &model, MyPolygon &polygon);

	// light
	LightCoefficient getColorAtPoint(Model &model, MyPolygon polygon, int x, int y, double z, Vector N);
	LightCoefficient getGouraudColorAt(Model &model, MyPolygon polygon, int x, int y, double z);
	COLORREF getPhongColorAt(Model &model, MyPolygon polygon, int x, int y);
	shadingTypes shadingType = FLAT_SHADING;
	LightCoefficient k_a = LightCoefficient(255, 255, 255);
	LightCoefficient k_s = LightCoefficient(255, 255, 255);
	LightCoefficient I_a = LightCoefficient(0.2, 0.2, 0.2);

	int background_image_height;
	int background_image_width;
	vector<COLORREF> background_image;
	bool show_background;
	bool tile_background;

	#define MAX_COUNT_OF_LIGHTSOURCES 7
	//std::vector<LightSource*> lightSources;
	LightSource* lightSources[MAX_COUNT_OF_LIGHTSOURCES] = { NULL };


	COLORREF originalColorOfHighlitedModel;
	int hilightedModelIndex = -1;
	int height, width;
	bool show_original_normals;
	bool draw_wireFrame;
	bool drawSilhouette = false;
	COLORREF silhouetteColor = RGB(255, 0, 0);
	Matrix perspectiveTransformation = Matrix(	Vector(1, 0, 0, 0),
												Vector(1, 0, 0, 0),
												Vector(0, 0, 2, 1),
												Vector(0, 0, -1, 0));
	double d, alpha;
	bool isPerspective = false;
	bool show_positive_normals;
};


