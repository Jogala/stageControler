#pragma once
#include "stageController.h"

class cut
{
private:
	stageController* pointerToE545;
	

public:
	void rectangle(double x, double y);
	cut(stageController &E545);
	~cut();
};

