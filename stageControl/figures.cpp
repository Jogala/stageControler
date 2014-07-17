#include "figures.h"
void figures::setRectangle(double a, double b, double phi0, double velo){

	rectangleVelo = velo;

	phi0 = phi0*(2 * pi) / (360.0);
	double deltaPhi[3];
	double R;
	double x, y, xOld, yOld;

	R = 0.5*sqrt(a*a + b*b);
	deltaPhi[0] = 2 * atan(b / a);
	deltaPhi[1] = 2 * atan(a / b);

	double deltaPhiSum = phi0 - deltaPhi[0] / 2.0;

	xOld = R*cos(phi0);
	yOld = R*sin(phi0);


	for (int i = 0; i <= 3; i++){

		deltaPhiSum = deltaPhiSum + deltaPhi[(i % 2)];

		x = R*cos(deltaPhiSum);
		y = R*sin(deltaPhiSum);

		rectangleRelCoordArray[i][0] = x - xOld;
		rectangleRelCoordArray[i][1] = y - yOld;

		xOld = x;
		yOld = y;
	}
	
}
//void figures::getRectangleRelCoord(double relCoord[4][2])
//{
//		for (int i = 0; i < 4; i++){
//			relCoord[i][0] = rectangleRelCoordArray[i][0];
//			relCoord[i][1] = rectangleRelCoordArray[i][1];
//		}
//}

double figures::getRectangleVelo()
{
	return rectangleVelo;
}


figures::figures()
{
}


figures::~figures()
{
}
