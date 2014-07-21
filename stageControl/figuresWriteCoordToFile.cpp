#include "figuresWriteCoordToFile.h"
void figuresWriteCoordToFile::rectangle::leaveOrSwapAdjustPhi(double &phi, double &a, double &b){

	while (phi < 0){
		phi = phi + 360;
	}
	double copyPhi = phi;

	phi = (phi / 360) * 2 * pi;
	phi = fmod(phi, 2 * pi);

	if (
		(
		(phi <= pi / 4) || (phi >= 7 * pi / 4) //phi ist minimal 0 und maximal 2*pi
		)
		||
		(
		(phi <= 5 * pi / 4) && (3 * pi / 4 <= phi)
		)
		)
	{
		//do nothing
	}
	else
	{
		double dummy = a;
		a = b;
		b = dummy;
		phi = copyPhi - 90;
	}
}

void figuresWriteCoordToFile::rectangle::set(double aIn, double bIn, double phi0In, double velocityIn){

	velocity = velocityIn;
	a = aIn;
	b = bIn;
	phi0 = phi0In*(2 * pi) / (360.0);


}


void figuresWriteCoordToFile::rectangle::cutAbsLim(){

//phi0, sa, sb dürfen durch diese Funktion nicht geändert werden
double sPhi = phi0;
double sa = a;
double sb = b;


leaveOrSwapAdjustPhi(sPhi, sa, sb);

use.degToRadByRef(sPhi);

double pos[3];
double deltaPhi[2];
double R;
double x, y, xOld, yOld;
double deltaX;
double deltaY;
double factor = 2;
double norm;

string name = "mainRecAbsLim.txt";
fstream f;
f << fixed;
f << setprecision(3);

f.open(name, fstream::out | fstream::trunc);
f.close();
f.open(name, fstream::out | fstream::app);

pos[0] = 100;
pos[1] = 100;
pos[2] = 100;

R = 0.5*sqrt(sa*sa + sb*sb);
deltaPhi[0] = 2 * atan(sb / sa);
deltaPhi[1] = 2 * atan(sa / sb);


double deltaPhiSum = sPhi - deltaPhi[0] / 2.0;

xOld = R*cos(deltaPhiSum) + pos[0];
yOld = R*sin(deltaPhiSum) + pos[1];

for (int i = 0; i <= 3; i++){

	if (i > 0){
		xOld = x;
		yOld = y;
	}

	deltaPhiSum = deltaPhiSum + deltaPhi[(i % 2)];

	x = R*cos(deltaPhiSum) + pos[0];
	y = R*sin(deltaPhiSum) + pos[1];


	norm = sqrt((x - xOld)*(x - xOld) + (y - yOld)*(y - yOld));
	deltaX = factor*(x - xOld) / norm;
	deltaY = factor*(y - yOld) / norm;
	//pointerToE545->moveTo(xOld - deltaX, yOld - deltaY, pos[2]);	//Fahren zu Position 1
	f << xOld - deltaX << "\t" << yOld - deltaY << endl;

	
	if (!(i % 2)){
		//pointerToE545->setLimits(2, y, yOld);					//set Limits A:B
		f << "\t \t " << 2 << "\t" << y << "\t" << yOld << endl;
	}
	else
	{
		//pointerToE545->setLimits(1, x, xOld);
		f << "\t \t " << 1 << "\t" << x << "\t" << xOld << endl;
	}



	//pointerToE545->moveTo(x + deltaX, y + deltaY, pos[2]);  //Fahre zu Position 2
	f << x + deltaX << "\t" << y + deltaY << endl;

}
//pointerToE545->setLimits(0, 0, 0);
//pointerToE545->moveTo(pos[0], pos[1], pos[2]);

f.close();

}




void figuresWriteCoordToFile::rectangle::cut()
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

void figuresWriteCoordToFile::surfaceRectangle::set(double aIn, double bIn, double phi0In, double velocityIn, int resolutionIn, char longOrShortSide){
	
	velocity = velocityIn;
	a = aIn;
	b = bIn;
	phi0 = phi0In*(2 * pi) / (360.0);
	resolution = resolutionIn;
	orientation = longOrShortSide;

}
void figuresWriteCoordToFile::surfaceRectangle::cut()
{
	double delta = b / resolution;
	//get Position
	//Set Limits 

	double deltaPhi[2];
	double R;
	double x0, y0;
	double h = 3;

	R = 0.5*sqrt(a*a + b*b);
	deltaPhi[0] = 2 * atan(b / a);
	deltaPhi[1] = 2 * atan(a / b);

	double phiStart = phi0 - deltaPhi[0] / 2.0;
		
	x0 = R*cos(phiStart);
	y0 = R*sin(phiStart);
	

	double deltaX = a*cos(phi0);
	double deltaY = b*sin(phi0);
	
	double kDeltaX = -cos(phi0)*h - sin(phi0)*delta / 2;
	double kDeltaY = -sin(phi0)*h + cos(phi0)*delta / 2;

	double zkDeltaX = cos(phi0)*h - sin(phi0)*delta / 2;
	double zkDeltaY = sin(phi0)*h + cos(phi0)*delta / 2;

	//move(x0,y0,0)
	//openShutter()
	for (int i = 0; i <= (resolution - 1);i++){
		//move(-deltaX,-deltaY,0)
		//move(kDeltaX,kDeltaY,0)
		//move(zkDeltaX,zkDeltaX,0)
		//move(deltaX,deltaY,0)
		//move(zkDeltaX,zkDeltaX,0)
		//move(kDeltaX,kDeltaY,0)
	}
	//move(-deltaX,-deltaY,0)

	//closeShutter()
	
}

void figuresWriteCoordToFile::polygon::set(double RIn, double phi0In, int stepsIn, double velocityIn){

	velocity = velocityIn;
	R = RIn;
	phi0 = phi0In*(2 * pi) / (360.0);
	steps = stepsIn;
}
void figuresWriteCoordToFile::polygon::cut()
{
	double x, y, xOld, yOld;
	double deltaPhi = (2 * pi) / steps;

	string name = "poly.txt";
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

		x = R*cos(phi0 + deltaPhi*i);
		y = R*sin(phi0 + deltaPhi*i);

		f << x << "\t\t\t" << y << endl;

		xOld = x;
		yOld = y;
	}
	f.close();
}



