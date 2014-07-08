#pragma once
#include "stageControler.h"

class cut
{
private:
	stageControler* pointerToE545;
	double spacialDelayX = 10; //µm
	double spacialDelayY = 10; //µm

public:
	void rectangle(double x, double y);
	cut(stageControler &E545);
	~cut();
};

