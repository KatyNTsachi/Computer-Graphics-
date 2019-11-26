#include "Camera.h"



Camera::Camera()
{
}

Camera::~Camera()
{
}

Matrix Camera::getTransformation()
{
	return InverseAffainTransformation * inverseRotationTransformation;
}

void Camera::scaleByInversOf(Matrix scale_matrix)
{
	inverseRotationTransformation = scale_matrix * inverseRotationTransformation;
	//rotationTransformation.printMatrix();
}

void Camera::rotateByInversOf(Matrix _rotationMatrix)
{
	inverseRotationTransformation = _rotationMatrix * inverseRotationTransformation;
}

void Camera::translateByInversOf(Matrix _affainMatrix)
{
	InverseAffainTransformation = _affainMatrix * InverseAffainTransformation;
}