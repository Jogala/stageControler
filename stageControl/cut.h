#pragma once
#include "stageControler.h"

class cut
{
private:
	stageControler* pointerToE545;
	double spacialDelayX = 10; //�m
	double spacialDelayY = 10; //�m

public:
	void rectangle(double x, double y);
	cut(stageControler &E545);
	~cut();
};

