#pragma once
#include"Matrix.h"

class Camera
{
public:
	Camera();
	~Camera();
	Matrix getTransformation();

private:
	Matrix tranformation;
	Matrix projection;
};

