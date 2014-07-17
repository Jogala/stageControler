#include "figures.h"
void figures::setRectangle(double a, double b, double phi0){

	phi0 = phi0*(2 * pi) / (360.0);
	double deltaPhi[3];
	double R;
	double x, y, xOld, yOld;
	string name = "RegPolygonRectangle.txt";

	R = 0.5*sqrt(a*a + b*b);
	deltaPhi[0] = 2 * atan(b / a);
	deltaPhi[1] = 2 * atan(a / b);

	double deltaPhiSum = phi0 - deltaPhi[0] / 2.0;

	xOld = R*cos(phi0);
	yOld = R*sin(phi0);

	fstream f;
	f << fixed;
	f << setprecision(3);

	f.open(name, fstream::out | fstream::trunc);
	f.close();
	f.open(name, fstream::out | fstream::app);

	for (int i = 0; i <= 3; i++){

		deltaPhiSum = deltaPhiSum + deltaPhi[(i % 2)];

		x = R*cos(deltaPhiSum);
		y = R*sin(deltaPhiSum);

		f << x - xOld << "\t\t\t" << y - yOld << endl;

		xOld = x;
		yOld = y;
	}
	f.close();
}
void figures::getRectangleRelCoord(double relCoord[2][4])
{
	string name = "RegPolygonRectangle.txt";
	fstream f;
	f.open(name, ios::in | ios::binary);

	if (!f.is_open()) {
		cout << "could not open " << name << endl;
	}
	else {
		for (int i = 0; i < 4; i++){
			f >> relCoord[0][i];
			f >> relCoord[1][i];
		}
	}
}


figures::figures()
{
}


figures::~figures()
{
}
