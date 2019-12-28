#include "stdafx.h"
#include "iritSkel.h"
#include "MyPolygon.h"
#include <iostream> 
#include <unordered_map>
Model model;
/*****************************************************************************
* Skeleton for an interface to a parser to read IRIT data files.			 *
******************************************************************************
* (C) Gershon Elber, Technion, Israel Institute of Technology                *
******************************************************************************
* Written by:  Gershon Elber				Ver 1.0, Feb 2002				 *
* Minimal changes made by Amit Mano			November 2008					 *
******************************************************************************/

IPFreeformConvStateStruct CGSkelFFCState = {
	FALSE,          /* Talkative */
	FALSE,          /* DumpObjsAsPolylines */
	TRUE,           /* DrawFFGeom */
	FALSE,          /* DrawFFMesh */
	{ 10, 10, 10 }, /* 10 isocurves peru/v/w direction. */
	100,            /* 100 point samples along a curve. */
	SYMB_CRV_APPROX_UNIFORM,  /* CrvApproxMethod */
	FALSE,   /* ShowIntrnal */
	FALSE,   /* CubicCrvsAprox */
	20,      /* Polygonal FineNess */
	FALSE,   /* ComputeUV */
	TRUE,    /* ComputeNrml */
	FALSE,   /* FourPerFlat */
	0,       /* OptimalPolygons */
	FALSE,   /* BBoxGrid */
	TRUE,    /* LinearOnePolyFlag */
	FALSE
};

//CGSkelProcessIritDataFiles(argv + 1, argc - 1);


/*****************************************************************************
* DESCRIPTION:                                                               *
* Main module of skeleton - Read command line and do what is needed...	     *
*                                                                            *
* PARAMETERS:                                                                *
*   FileNames:  Files to open and read, as a vector of strings.              *
*   NumFiles:   Length of the FileNames vector.								 *
*                                                                            *
* RETURN VALUE:                                                              *
*   bool:		false - fail, true - success.                                *
*****************************************************************************/
bool CGSkelProcessIritDataFiles(CString &FileNames, int NumFiles, int _number_of_polygons)
{
	IPObjectStruct *PObjects;
	IrtHmgnMatType CrntViewMat;

	/* Get the data files: */
	IPSetFlattenObjects(FALSE);
	CStringA CStr(FileNames);
	if ((PObjects = IPGetDataFiles((const char* const *)&CStr, 1/*NumFiles*/, TRUE, FALSE)) == NULL)
		return false;
	PObjects = IPResolveInstances(PObjects);

	if (IPWasPrspMat)
		MatMultTwo4by4(CrntViewMat, IPViewMat, IPPrspMat);
	else
		IRIT_GEN_COPY(CrntViewMat, IPViewMat, sizeof(IrtHmgnMatType));

	/* Here some useful parameters to play with in tesselating freeforms: */
	CGSkelFFCState.FineNess = _number_of_polygons;   /* Res. of tesselation, larger is finer. */
	CGSkelFFCState.ComputeUV = TRUE;   /* Wants UV coordinates for textures. */
	CGSkelFFCState.FourPerFlat = TRUE;/* 4 poly per ~flat patch, 2 otherwise.*/
	CGSkelFFCState.LinearOnePolyFlag = TRUE;    /* Linear srf gen. one poly. */

	/* Traverse ALL the parsed data, recursively. */
	IPTraverseObjListHierarchy(PObjects, CrntViewMat,
        CGSkelDumpOneTraversedObject);
	return true;
}

/*****************************************************************************
* DESCRIPTION:                                                               *
*   Call back function of IPTraverseObjListHierarchy. Called on every non    *
* list object found in hierarchy.                                            *
*                                                                            *
* PARAMETERS:                                                                *
*   PObj:       Non list object to handle.                                   *
*   Mat:        Transformation matrix to apply to this object.               *
*   Data:       Additional data.                                             *
*                                                                            *
* RETURN VALUE:                                                              *
*   void									                                 *
*****************************************************************************/
void CGSkelDumpOneTraversedObject(IPObjectStruct *PObj,
                                  IrtHmgnMatType Mat,
                                  void *Data)
{
	IPObjectStruct *PObjs;

	if (IP_IS_FFGEOM_OBJ(PObj))
		PObjs = IPConvertFreeForm(PObj, &CGSkelFFCState);
	else
		PObjs = PObj;

	for (PObj = PObjs; PObj != NULL; PObj = PObj -> Pnext)
		if (!CGSkelStoreData(PObj)) 
			exit(1);
}


struct KeyHasher
{
	std::size_t operator()(const Point& k) const
	{
		using std::size_t;
		using std::hash;
		using std::string;
		double tmp = k.getX() + k.getY() + k.getZ();
		return std::hash<double>() (tmp);
	}
};

/*****************************************************************************
* DESCRIPTION:                                                               *
*   Prints the data from given geometry object.								 *
*                                                                            *
* PARAMETERS:                                                                *
*   PObj:       Object to print.                                             *
*   Indent:     Column of indentation.                                       *
*                                                                            *
* RETURN VALUE:                                                              *
*   bool:		false - fail, true - success.                                *
*****************************************************************************/
bool CGSkelStoreData(IPObjectStruct *PObj)
{
	int i;
	const char *Str;
	double RGB[3], Transp;
	IPPolygonStruct *PPolygon;
	IPVertexStruct *PVertex;
	IPVertexStruct *PVertex1;
	IPVertexStruct *PVertex2;

	const IPAttributeStruct *Attrs =
        AttrTraceAttributes(PObj -> Attr, PObj -> Attr);

	if (PObj -> ObjType != IP_OBJ_POLY) {
		AfxMessageBox(_T("Non polygonal object detected and ignored"));
		return true;
	}

	/* You can use IP_IS_POLYGON_OBJ(PObj) and IP_IS_POINTLIST_OBJ(PObj) 
	   to identify the type of the object*/

	if (CGSkelGetObjectColor(PObj, RGB))
	{
		int tmp_RGB[3];
		tmp_RGB[0] = RGB[0] * 255;
		tmp_RGB[1] = RGB[1] * 255;
		tmp_RGB[2] = RGB[2] * 255;
		model.setColor(tmp_RGB);
	}
	if (CGSkelGetObjectTransp(PObj, &Transp))
	{
		/* transparency code */
	}
	if ((Str = CGSkelGetObjectTexture(PObj)) != NULL)
	{
		/* volumetric texture code */
	}
	if ((Str = CGSkelGetObjectPTexture(PObj)) != NULL)
	{
		/* parametric texture code */
	}
	if (Attrs != NULL) 
	{
		printf("[OBJECT\n");
		while (Attrs) {
			/* attributes code */
			Attrs = AttrTraceAttributes(Attrs, NULL);
		}
	}
	//////////////////////////////////////////////////////// create hash table//////////////////////////////////////////////////////////////////////
	unordered_map<Point, vector<Vector>, KeyHasher> original_point_hush_table;
	unordered_map<Point, vector<Vector>, KeyHasher> calculated_point_hush_table;

	bool first = true;
	for (PPolygon = PObj -> U.Pl; PPolygon != NULL;	PPolygon = PPolygon -> Pnext) 
	{
			if (PPolygon -> PVertex == NULL) {
				AfxMessageBox(_T("Dump: Attemp to dump empty polygon"));
				return false;
			}

			MyPolygon polygon;
			Vector polygon_original_normal;
			Vector polygon_calculated_normal = calculatorPlaneNormal(PPolygon);

			if (IP_HAS_PLANE_POLY(PPolygon))
			{
				polygon_original_normal[0] = PPolygon->Plane[0];
				polygon_original_normal[1] = PPolygon->Plane[1];
				polygon_original_normal[2] = PPolygon->Plane[2];
			}
			else
			{
				polygon_original_normal = polygon_calculated_normal;
			}

			//set the polygon normals
			polygon.setOriginalNormal(polygon_original_normal);
			polygon.setCalculatedNormal(polygon_calculated_normal);

			//addin all points to polygon
			PVertex = PPolygon->PVertex;
			Point p1, p2, center;

			p1.setX(PVertex->Coord[0]);
			p1.setY(PVertex->Coord[1]);
			p1.setZ(PVertex->Coord[2]);

			if (IP_HAS_NORMAL_VRTX(PVertex))
			{
				p1.setOriginalNormal(Vector(PVertex->Normal[0], PVertex->Normal[1], PVertex->Normal[2], 0));
			}


			int vertexCount = 1;
			center = p1;
			bool LastLine = false;
			//add all the vertex to our polygon
			for (PVertex = PPolygon->PVertex->Pnext; true; PVertex = PVertex->Pnext)
			{
				if (PVertex == NULL)
				{
					PVertex = PPolygon->PVertex;
					LastLine = true;
				}
				//set the new point to p2
				p2.setX(PVertex->Coord[0]);
				p2.setY(PVertex->Coord[1]);
				p2.setZ(PVertex->Coord[2]);



				//calc center of polygon
				center.setX(center.getX() + p2.getX());
				center.setY(center.getY() + p2.getY());
				center.setZ(center.getZ() + p2.getZ());
				vertexCount++;

				//add normal
				if (IP_HAS_NORMAL_VRTX(PVertex))
				{
					p2.setOriginalNormal(Vector(PVertex->Normal[0], PVertex->Normal[1], PVertex->Normal[2], 0));
				}

				polygon.addLine(Line(p1, p2));

				//add vertex to hash

				original_point_hush_table[p1].push_back(polygon_original_normal);
				calculated_point_hush_table[p1].push_back(polygon_calculated_normal);

				p1 = p2;

				if (LastLine)
					break;

			}

			//set center of polygon
			polygon.setCenter(Point(center.getX() / vertexCount, center.getY() / vertexCount, center.getZ() / vertexCount));

			model.addPolygon(polygon);
	}
	//////////////////////////////////////////////////////// create hash table//////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////// add vertex normals///////////////////////////////////////////////////////////////////////
	vector<MyPolygon> list_of_polygons = model.getModelPolygons();

	for (vector<MyPolygon>::iterator tmp_polygon = list_of_polygons.begin(); tmp_polygon != list_of_polygons.end(); tmp_polygon++)
	{

		vector<Line> list_of_lines = tmp_polygon->getLines();

		for (auto tmp_line = list_of_lines.begin(); tmp_line != list_of_lines.end(); tmp_line++)
		{

			//for the calculated normals
			Point p1 = tmp_line->getP1();
			double x = 0, y = 0, z = 0;
			int tmp_counter = 0;
			for (auto tmp_normal = calculated_point_hush_table[p1].begin(); tmp_normal != calculated_point_hush_table[p1].end(); tmp_normal++)
			{
				x = x + (*tmp_normal)[0];
				y = y + (*tmp_normal)[1];
				z = z + (*tmp_normal)[2];
				tmp_counter = tmp_counter + 1;
			}
			if (tmp_counter != 0)
				p1.setCalculatedNormal(Vector(x / tmp_counter, y / tmp_counter, z / tmp_counter, 0));

			//for the original normals
			if (p1.getOriginalNormal() == Vector(0, 0, 0, 0))
			{
				double x = 0, y = 0, z = 0;
				int tmp_counter = 0;
				for (auto tmp_normal = original_point_hush_table[p1].begin(); tmp_normal != original_point_hush_table[p1].end(); tmp_normal++)
				{
					x = x + (*tmp_normal)[0];
					y = y + (*tmp_normal)[1];
					z = z + (*tmp_normal)[2];
					tmp_counter = tmp_counter + 1;
				}
				if (tmp_counter != 0)
					p1.setOriginalNormal(Vector(x / tmp_counter, y / tmp_counter, z / tmp_counter, 0));
			}

			tmp_line->setP1(p1);

			////////////////////// p2 ////////////////////////////////

			Point p2 = tmp_line->getP2();
			x = 0, y = 0, z = 0;
			tmp_counter = 0;
			for (auto tmp_normal = calculated_point_hush_table[p2].begin(); tmp_normal != calculated_point_hush_table[p2].end(); tmp_normal++)
			{
				x = x + (*tmp_normal)[0];
				y = y + (*tmp_normal)[1];
				z = z + (*tmp_normal)[2];
				tmp_counter = tmp_counter + 1;
			}
			if (tmp_counter != 0)
				p2.setCalculatedNormal(Vector(x / tmp_counter, y / tmp_counter, z / tmp_counter, 0));

			//for the original normals
			if (p2.getOriginalNormal() == Vector(0, 0, 0, 0))
			{
				double x = 0, y = 0, z = 0;
				int tmp_counter = 0;
				for (auto tmp_normal = original_point_hush_table[p2].begin(); tmp_normal != original_point_hush_table[p2].end(); tmp_normal++)
				{
					x = x + (*tmp_normal)[0];
					y = y + (*tmp_normal)[1];
					z = z + (*tmp_normal)[2];
					tmp_counter = tmp_counter + 1;
				}
				if (tmp_counter != 0)
					p2.setOriginalNormal(Vector(x / tmp_counter, y / tmp_counter, z / tmp_counter, 0));
			}

			tmp_line->setP2(p2);

		}
		tmp_polygon->setListOfLines(list_of_lines);
	}

	model.setListOfPolygons(list_of_polygons);
	return true;
}

/*****************************************************************************
* DESCRIPTION:                                                               *
*   Returns the color of an object.                                          *
*                                                                            *
* PARAMETERS:                                                                *
*   PObj:   Object to get its color.                                         *
*   RGB:    as 3 floats in the domain [0, 1].                                *
*                                                                            *
* RETURN VALUE:                                                              *
*   int:    TRUE if object has color, FALSE otherwise.                       *
*****************************************************************************/
int CGSkelGetObjectColor(IPObjectStruct *PObj, double RGB[3])
{
	static int TransColorTable[][4] = {
		{ /* BLACK	*/   0,    0,   0,   0 },
		{ /* BLUE	*/   1,    0,   0, 255 },
		{ /* GREEN	*/   2,    0, 255,   0 },
		{ /* CYAN	*/   3,    0, 255, 255 },
		{ /* RED	*/   4,  255,   0,   0 },
		{ /* MAGENTA 	*/   5,  255,   0, 255 },
		{ /* BROWN	*/   6,   50,   0,   0 },
		{ /* LIGHTGRAY	*/   7,  127, 127, 127 },
		{ /* DARKGRAY	*/   8,   63,  63,  63 },
		{ /* LIGHTBLUE	*/   9,    0,   0, 255 },
		{ /* LIGHTGREEN	*/   10,   0, 255,   0 },
		{ /* LIGHTCYAN	*/   11,   0, 255, 255 },
		{ /* LIGHTRED	*/   12, 255,   0,   0 },
		{ /* LIGHTMAGENTA */ 13, 255,   0, 255 },
		{ /* YELLOW	*/   14, 255, 255,   0 },
		{ /* WHITE	*/   15, 255, 255, 255 },
		{ /* BROWN	*/   20,  50,   0,   0 },
		{ /* DARKGRAY	*/   56,  63,  63,  63 },
		{ /* LIGHTBLUE	*/   57,   0,   0, 255 },
		{ /* LIGHTGREEN	*/   58,   0, 255,   0 },
		{ /* LIGHTCYAN	*/   59,   0, 255, 255 },
		{ /* LIGHTRED	*/   60, 255,   0,   0 },
		{ /* LIGHTMAGENTA */ 61, 255,   0, 255 },
		{ /* YELLOW	*/   62, 255, 255,   0 },
		{ /* WHITE	*/   63, 255, 255, 255 },
		{		     -1,   0,   0,   0 }
	};
	int i, j, Color, RGBIColor[3];

	if (AttrGetObjectRGBColor(PObj,
		&RGBIColor[0], &RGBIColor[1], &RGBIColor[2])) {
			for (i = 0; i < 3; i++)
				RGB[i] = RGBIColor[i] / 255.0;

			return TRUE;
	}
	else if ((Color = AttrGetObjectColor(PObj)) != IP_ATTR_NO_COLOR) {
		for (i = 0; TransColorTable[i][0] >= 0; i++) {
			if (TransColorTable[i][0] == Color) {
				for (j = 0; j < 3; j++)
					RGB[j] = TransColorTable[i][j+1] / 255.0;
				return TRUE;
			}
		}
	}

	return FALSE;
}

/*****************************************************************************
* DESCRIPTION:                                                               *
*   Returns the volumetric texture of an object, if any.                     *
*                                                                            *
* PARAMETERS:                                                                *
*   PObj:   Object to get its volumetric texture.                            *
*                                                                            *
* RETURN VALUE:                                                              *
*   char *:    Name of volumetric texture map to apply, NULL if none.        *
*****************************************************************************/
const char *CGSkelGetObjectTexture(IPObjectStruct *PObj)
{
	return AttrGetObjectStrAttrib(PObj, "texture");
}

/*****************************************************************************
* DESCRIPTION:                                                               *
*   Returns the parametric texture of an object, if any.                     *
*                                                                            *
* PARAMETERS:                                                                *
*   PObj:   Object to get its parametric texture.                            *
*                                                                            *
* RETURN VALUE:                                                              *
*   char *:    Name of parametric texture map to apply, NULL if none.        *
*****************************************************************************/
const char *CGSkelGetObjectPTexture(IPObjectStruct *PObj)
{
	return AttrGetObjectStrAttrib(PObj, "ptexture");
}

/*****************************************************************************
* DESCRIPTION:                                                               *
*   Returns the transparency level of an object, if any.                     *
*                                                                            *
* PARAMETERS:                                                                *
*   PObj:   Object to get its volumetric texture.                            *
*   Transp: Transparency level between zero and one.                         *
*                                                                            *
* RETURN VALUE:                                                              *
*   int:    TRUE if object has transparency, FALSE otherwise.                *
*****************************************************************************/
int CGSkelGetObjectTransp(IPObjectStruct *PObj, double *Transp)
{
	*Transp = AttrGetObjectRealAttrib(PObj, "transp");

	return !IP_ATTR_IS_BAD_REAL(*Transp);
}

/*****************************************************************************
* DESCRIPTION:                                                               *
*   Computes the INVERSE of a given matrix M.								 *
*	The matrix M is is not modified.										 *
*   The matrix M is assumed to be 4 by 4 (a transformation matrix).			 *
*   Return TRUE if the inverted matrix (InvM) exists.						 *
*                                                                            *
* PARAMETERS:                                                                *
*   M:          Original matrix to invert.                                   *
*   InvM:       Inverted matrix will be placed here.						 *
*                                                                            *
* RETURN VALUE:                                                              *
*   int:        TRUE if inverse exists, FALSE otherwise.                     *
*****************************************************************************/
int CGSkelInverseMatrix(double M[4][4], double InvM[4][4])
{	
	return MatInverseMatrix(M, InvM);
}

Vector calculatorPlaneNormal(IPPolygonStruct* PPolygon)
{
	IPVertexStruct* v0 = PPolygon->PVertex;
	IPVertexStruct* v1 = PPolygon->PVertex->Pnext;
	IPVertexStruct* v2 = PPolygon->PVertex->Pnext->Pnext;


	Vector vector1(v2->Coord[0] - v1->Coord[0], v2->Coord[1] - v1->Coord[1], v2->Coord[2] - v1->Coord[2], 0);
	Vector vector2(v0->Coord[0] - v1->Coord[0], v0->Coord[1] - v1->Coord[1], v0->Coord[2] - v1->Coord[2], 0);

	Vector res(vector1[1] * vector2[2] - vector1[2] * vector2[1],
		-(vector1[0] * vector2[2] - vector1[2] * vector2[0]),
		vector1[0] * vector2[1] - vector1[1] * vector2[0], 0);

	return res;
}