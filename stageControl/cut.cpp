#include "cut.h"


void cut::rectangle(double x, double y){

	double del = 10;//cant be choosen bigger then 10 if max(x)=180 or max(y)=180;
	double spacialDelayX = 10; //µm
	double spacialDelayY = 10; //µm

	//s.t. there will not be a cut in the beginning into the wrong place

		if ((x > 160) || (y >= 160)){
			std::cout << "Chosen dimensions for the rectangle too big." << std::endl;
		}
		else
		{
			pointerToE545->moveTo(100 - 0.5*x - spacialDelayX, 100 + 0.5*y, 100);
			pointerToE545->minMaxTrigger(1, 100 - 0.5*x, 100 + 0.5*x + del);
			pointerToE545->moveTo(100 + 0.5*x, 100 + 0.5*y, 100);
			pointerToE545->moveTo(100 + 0.5*x, 100 - 0.5*y, 100);
			pointerToE545->minMaxTrigger(1, 100 - 0.5*x-del, 100 + 0.5*x + del);
			pointerToE545->moveTo(100 - 0.5*x, 100 - 0.5*y, 100);
			pointerToE545->moveTo(100 - 0.5*x, 100 + 0.5*y, 100);
			pointerToE545->minMaxTrigger(1, 100 - 0.5*x-1, 100 + 0.5*y);
			pointerToE545->moveTo(100 - 0.5*x-spacialDelayX, 100 + 0.5*y, 100);
		}
}

cut::cut(stageController &E545)
{
	pointerToE545 = &E545;
}


cut::~cut()
{
}
