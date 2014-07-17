#pragma once
#include "Header.h"

using namespace std; 



class figures
{
private: 
	double pi = 3.1415926535897932384626;


public:

	void getRectangleRelCoord(double relCoord[2][4]);
	void setRectangle(double a, double b, double phi0);
	

	figures();
	~figures();
};

