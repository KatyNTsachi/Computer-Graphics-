#include "MyPolygon.h"
#include "Vector.h"
#include "Matrix.h"
#include "Line.h"


MyPolygon::MyPolygon()
{
	lines = std::vector<Line>();
}

MyPolygon::~MyPolygon()
{
}

void MyPolygon::addLine(Line line)
{
	lines.push_back(line);
}

std::vector<Line>& MyPolygon::getLines()
{
	return lines;
}


void MyPolygon::setCenter(Point _p)
{
	center_of_polygon = _p;
}

Point MyPolygon::getCenter()
{
	return center_of_polygon;
}

void MyPolygon::setOriginalNormal(Vector _normal)
{
	original_normal = _normal;
}

void MyPolygon::setCalculatedNormal(Vector _normal)
{
	calculated_normal = _normal;
}

Vector MyPolygon::getOriginalNormal()
{
	return original_normal;
}

Vector MyPolygon::getCalculatedNormal()
{
	return calculated_normal;
}

void MyPolygon::setListOfLines(std::vector<Line> _list_of_lines)
{
	lines = _list_of_lines;
}

MyPolygon MyPolygon::tranformPolygon(Matrix tranformation_matrix)
{
	MyPolygon new_poly;

	//calculate normal
	//Vector NCalculated = tranformation_matrix.getTranformation(calculated_normal);
	
	
	//Vector NVertexCalculated, NVertexOriginal;
	Vector NCalculated = calculated_normal;
	Line tmp_Line = Line(Point(0, 0, 0), Point(NCalculated[0], NCalculated[1], NCalculated[2])).tranformLine(tranformation_matrix);
	NCalculated[0] = tmp_Line.getP2().getX() - tmp_Line.getP1().getX();
	NCalculated[1] = tmp_Line.getP2().getY() - tmp_Line.getP1().getY();
	NCalculated[2] = tmp_Line.getP2().getZ() - tmp_Line.getP1().getZ();
	
	new_poly.calculated_normal = NCalculated * (1 / sqrt( pow(NCalculated[0],2) + pow(NCalculated[1], 2) + pow(NCalculated[2], 2) ));


	//Vector NVertexCalculated, NVertexOriginal;
	Vector NOriginal = original_normal;
	tmp_Line = Line(Point(0, 0, 0), Point(NOriginal[0], NOriginal[1], NOriginal[2])).tranformLine(tranformation_matrix);
	NOriginal[0] = tmp_Line.getP2().getX() - tmp_Line.getP1().getX();
	NOriginal[1] = tmp_Line.getP2().getY() - tmp_Line.getP1().getY();
	NOriginal[2] = tmp_Line.getP2().getZ() - tmp_Line.getP1().getZ();

	new_poly.original_normal = NOriginal * (1 / sqrt(pow(NOriginal[0], 2) + pow(NOriginal[1], 2) + pow(NOriginal[2], 2)));


	std::vector<Line> Transformedlines;

	for (auto line = lines.begin(); line != lines.end(); line++)
	{
		Transformedlines.push_back(line->tranformLine(tranformation_matrix));
	}
	new_poly.setListOfLines(Transformedlines);
	new_poly.center_of_polygon = tranformation_matrix.getTranformation(this->center_of_polygon); // this->center_of_polygon * tranformation_matrix;

	return new_poly;
}