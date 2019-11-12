#pragma once
#include"Matrix.h"

class Camera
{
public:
	Camera();
	~Camera();

private:
	Matrix tranformation;
	Matrix projection;
};

