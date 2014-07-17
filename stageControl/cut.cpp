#include "cut.h"


void cut::rectangle(){

	//only because xRectangle is very long... 
	double x = xRectangle;
	double y = yRectangle;
	double del = 10;//cant be choosen bigger then 10 if max(x)=180 or max(y)=180;
	double spacialDelayX = 10; //µm
	double spacialDelayY = 10; //µm

	double pos[3];
	pointerToE545->getPositon(pos);

	if (useful.qValuesInLimits(x + pos[1], y + pos[2]))
	{
		pointerToE545->moveTo(100 - 0.5*x - spacialDelayX, 100 + 0.5*y, 100);
		pointerToE545->setLimits(1, 100 - 0.5*x, 100 + 0.5*x + del);
		pointerToE545->moveTo(100 + 0.5*x, 100 + 0.5*y, 100);
		pointerToE545->moveTo(100 + 0.5*x, 100 - 0.5*y, 100);
		pointerToE545->setLimits(1, 100 - 0.5*x - del, 100 + 0.5*x + del);
		pointerToE545->moveTo(100 - 0.5*x, 100 - 0.5*y, 100);
		pointerToE545->moveTo(100 - 0.5*x, 100 + 0.5*y, 100);
		pointerToE545->setLimits(1, 100 - 0.5*x - 1, 100 + 0.5*y);
		pointerToE545->moveTo(100 - 0.5*x - spacialDelayX, 100 + 0.5*y, 100);
	}
	else
	{
		cout << "Can't cut because values are not in [0,200]" << endl;
	}
}




































cut::cut(stageController &E545)
{
	pointerToE545 = &E545;
}

cut::~cut()
{
}
