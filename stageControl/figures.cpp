#include "figures.h"
void figures::rectangle::set(double aIn, double bIn, double phi0In, double velocityIn){

	velocity = velocityIn;
	a = aIn;
	b = bIn;
	phi0 = phi0In*(2 * pi) / (360.0);


}
void figures::rectangle::cut()
{
	double deltaPhi[2];
	double R;
	double x, y, xOld, yOld;
	
	
	R = 0.5*sqrt(a*a + b*b);
	deltaPhi[0] = 2 * atan(b / a);
	deltaPhi[1] = 2 * atan(a / b);

	string name = "rectangle.txt";
	fstream f;
	f << fixed;
	f << setprecision(3);

	f.open(name, fstream::out | fstream::trunc);
	f.close();
	f.open(name, fstream::out | fstream::app);


	double deltaPhiSum = phi0 - deltaPhi[0] / 2.0;

	xOld = R*cos(deltaPhiSum);
	yOld = R*sin(deltaPhiSum);

	f << xOld << "\t\t\t" << yOld << endl;

	for (int i = 1; i <= 3; i++){

		deltaPhiSum = deltaPhiSum + deltaPhi[(i % 2)];
		
		x = R*cos(deltaPhiSum);
		y = R*sin(deltaPhiSum);

		f << x << "\t\t\t" << y << endl;

		xOld = x;
		yOld = y;
	}
	f.close();
}

void figures::polygon::set(double RIn, double phi0In, int stepsIn, double velocityIn){

	velocity = velocityIn;
	R = RIn;
	phi0 = phi0In*(2 * pi) / (360.0);
	steps = stepsIn;
}
void figures::polygon::cut()
{
	double x, y, xOld, yOld;
	double deltaPhi = (2 * pi) / steps;

	string name = "circle.txt";
	fstream f;
	f << fixed;
	f << setprecision(3);

	f.open(name, fstream::out | fstream::trunc);
	f.close();
	f.open(name, fstream::out | fstream::app);

	xOld = R*cos(phi0);
	yOld = R*sin(phi0);

	f << xOld << "\t\t\t" << yOld << endl;

	for (int i = 1; i <= steps; i++){

		x = R*cos(phi0+deltaPhi*i);
		y = R*sin(phi0+deltaPhi*i);

		f << x << "\t\t\t" << y << endl;

		xOld = x;
		yOld = y;
	}
	f.close();
}




figures::figures()
{
}


figures::~figures()
{
}