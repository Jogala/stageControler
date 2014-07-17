#pragma once
#include "Header.h"

using namespace std; 



class figures
{
private: 
	double pi = 3.1415926535897932384626;

public:

	//rectangle
	double rectangleRelCoordArray[4][2];
	double rectangleVelo;
	//void getRectangleRelCoord(double relCoord[4][2]);
	void setRectangle(double a, double b, double phi0, double velo);
	double getRectangleVelo();

		

	

	figures();
	~figures();
};

