#include "cut.h"

void cut::setRectangle(double x, double y){
	if ((x <= 200) && (y <= 200)){
		xRectangle = x;
		yRectangle = y;
	}
	else
	{
		cout << "out of limits, old values are kept" << endl;
	}
}
void cut::setCircle(double r, double velocity){
	if (r <= 100){
		circleRadius = r;
		circleVelocity = velocity;
	}
	else
	{
		cout << "out of limits, old values are kept" << endl;
	}
}
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
void cut::circle(){
	double R = circleRadius;
	double x;
	double y;
	int steps = 100;
	double deltaPhi = 2 * pi / steps;
	double pos[3];

	pointerToE545->setVelocity(20, 20, 0);

	double xOld, yOld, deltaX, deltaY;
	xOld = R;
	yOld = 0;
	pointerToE545->move(xOld, yOld, 0);

	cout << "Start cutting circle" << endl;
	pointerToE545->openShutter();

	for (int i = 1; i < steps; i++){

		x = R*cos(deltaPhi*i);
		y = R*sin(deltaPhi*i);

		deltaX = x - xOld;
		deltaY = y - yOld;

		xOld = x;
		yOld = y;

		pointerToE545->move(deltaX, deltaY, 0);

	}
	pointerToE545->closeShutter();
	cout << "Finished cutting circle" << endl;
}



































cut::cut(stageController &E545)
{
	pointerToE545 = &E545;
}

cut::~cut()
{
}
