#pragma once
#include "stageController.h"
#include "usefulFunctions.h"

class cut
{
private:
	stageController* pointerToE545;
	usefulFunctions useful;

	//rectangle
	double xRectangle;
	double yRectangle;
	
public:

	void setRectangle(double x, double y);
	void rectangle();

	cut(stageController &E545);
	~cut();
};

