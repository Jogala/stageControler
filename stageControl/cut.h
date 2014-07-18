#pragma once
#include "stageController.h"
#include "usefulFunctions.h"

class cut
{
private:
	stageController* pointerToE545;
	usefulFunctions useful;

	//circle 
	double circleRadius;
	double circleVelocity;

	//rectangle
	double xRectangle;
	double yRectangle;

	//P4 = regPolygonRectangle 4 Eck 
	
	
	
public:

	void setRectangle(double x, double y);
	void rectangle();

	void setCircle(double r, double velocity);
	void circle();

	void regPolygonRectangle();
	void setRegPolygonRectangle(double a, double b, double phi0);

	cut(stageController &E545);
	~cut();
};

