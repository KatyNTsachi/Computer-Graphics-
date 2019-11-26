#pragma once
#include"Matrix.h"

class Camera
{
public:
	Camera();
	~Camera();
	Matrix getTransformation();
	void scaleByInversOf(Matrix scale_matrix);
	void rotateByInversOf(Matrix rotationMatrix);
	void translateByInversOf(Matrix affainMatrix);

private:
	Matrix inverseRotationTransformation;
	Matrix InverseAffainTransformation;
};

