#include "stdafx.h"
#include "func.h"

#include <math.h> 


using namespace std;
#include <sstream>
#include <iostream>
#include <string.h>


func::func(int a_, int b_, int s_)
{
	a = a_;
	b = b_;
	s = s_;
}


func::~func()
{
}

double func::getValue(int x, int y){
	
	/*
	std::string  str = std::to_string(w);
	std::wstring widestr = std::wstring(str.begin(), str.end());
	const wchar_t *c = widestr.c_str();
	AfxMessageBox(c, MB_OK);
	*/
	
	double tmp1 = a * (x - 0.5*w);
	tmp1 = pow(tmp1, 4);
	double tmp2 = b * (y - 0.5*h);
	tmp2 = pow(tmp2, 4);
	double res =  cos(( tmp1 + tmp2 )/pow(s, 3));
	
	return res;
}