#include "figures.h"

void figures::rectangle::leaveOrSwap(double &phi, double &a, double &b){

	while (phi < 0){
		phi = phi + 360;
	}
	double copyPhi = phi;

	phi = (phi / 360) * 2 * pi;
	phi = fmod(phi, 2 * pi);
	cout << (phi / (2 * pi)) * 360 << endl;
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

void figures::rectangle::set(double aIn, double bIn, double phi0In, double velocityIn){

	velocity = velocityIn;
	a = aIn;
	b = bIn;
	phi0 = phi0In*(2 * pi) / (360.0);

}

void figures::rectangle::cutRel()
{

	pointerToE545->setVelocity(velocity, velocity, 10);
	double deltaPhi[2];
	double R;
	double x, y, xOld, yOld;
	double pos[3];

	pointerToE545->getPositon(pos);

	R = 0.5*sqrt(a*a + b*b);
	deltaPhi[0] = 2 * atan(b / a);
	deltaPhi[1] = 2 * atan(a / b);

	double deltaPhiSum = phi0 - deltaPhi[0] / 2.0;

	xOld = R*cos(deltaPhiSum);
	yOld = R*sin(deltaPhiSum);

	pointerToE545->move(xOld, yOld, 0);

	pointerToE545->openShutter();
	for (int i = 1; i <= 4; i++){

		deltaPhiSum = deltaPhiSum + deltaPhi[(i % 2)];

		x = R*cos(deltaPhiSum);
		y = R*sin(deltaPhiSum);

		pointerToE545->move(x - xOld, y - yOld, 0);

		xOld = x;
		yOld = y;
	}
	pointerToE545->closeShutter();
	pointerToE545->moveTo(pos);
}
void figures::rectangle::cutAbs()
{

	pointerToE545->setVelocity(velocity, velocity, 10);

	double pos[3];
	double deltaPhi[2];
	double R;
	double x, y, xOld, yOld;

	pointerToE545->getPositon(pos);

	R = 0.5*sqrt(a*a + b*b);
	deltaPhi[0] = 2 * atan(b / a);
	deltaPhi[1] = 2 * atan(a / b);

	double deltaPhiSum = phi0 - deltaPhi[0] / 2.0;

	xOld = R*cos(deltaPhiSum);
	yOld = R*sin(deltaPhiSum);

	pointerToE545->moveTo(xOld + pos[0], yOld + pos[1], pos[2]);

	pointerToE545->openShutter();
	for (int i = 1; i <= 4; i++){

		deltaPhiSum = deltaPhiSum + deltaPhi[(i % 2)];

		x = R*cos(deltaPhiSum);
		y = R*sin(deltaPhiSum);

		pointerToE545->moveTo(x + pos[0], y + pos[1], pos[2]);

		xOld = x;
		yOld = y;
	}
	pointerToE545->closeShutter();
	pointerToE545->moveTo(pos[0], pos[1], pos[2]);
}
void figures::rectangle::cutAbsLim()
{
	pointerToE545->setVelocity(velocity, velocity, 10);

	double sPhi = phi0;
	double sa = a; 
	double sb = b;
	leaveOrSwap(sPhi, sa, sb);

	double pos[3];
	double deltaPhi[2];
	double R;
	double x, y, xOld, yOld;
	double deltaX;
	double deltaY;
	double factor=2;
	double norm;

	pointerToE545->getPositon(pos);

	R = 0.5*sqrt(sa*sa + sb*sb);
	deltaPhi[0] = 2 * atan(sb / sa);
	deltaPhi[1] = 2 * atan(sa / sb);

	double deltaPhiSum = sPhi - deltaPhi[0] / 2.0;

	for (int i = 0; i <= 4; i++){

		if (i > 0){
			xOld = x;
			yOld = y;
		}


		deltaPhiSum = deltaPhiSum + deltaPhi[(i % 2)];
		
		x = R*cos(deltaPhiSum) + pos[0];
		y = R*sin(deltaPhiSum) + pos[1];

		if (i>=2)
		{
			norm = sqrt((x - xOld)*(x - xOld) + (y - yOld)*(y - yOld));
			deltaX=factor*(x - xOld)/norm;
			deltaY=factor*(y - yOld)/norm;
			pointerToE545->moveTo(xOld-deltaX, yOld-deltaY, 0);	//Fahren zu Position 1

			pointerToE545->setLimits((i+1)%2+1,y,yOld);					//set Limits A:B
			pointerToE545->moveTo(x+deltaX, y+deltaY, pos[2]);  //Fahre zu Position 2
		}		
	}
	pointerToE545->setLimits(0, 0, 0);
	pointerToE545->moveTo(pos[0], pos[1], pos[2]);
}


void figures::surfaceRectangle::set(double aIn, double bIn, double phi0In, double velocityIn, int resolutionIn, char longOrShortSide){


	velocity = velocityIn;
	a = aIn;
	b = bIn;
	phi0 = phi0In*(2 * pi) / (360.0);
	resolution = resolutionIn;
	orientation = longOrShortSide;

}
void figures::surfaceRectangle::cutRel()
{
	pointerToE545->setVelocity(velocity, velocity, 10);
	double delta = b / resolution;

	double pos[3];
	pointerToE545->getPositon(pos);

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

	pointerToE545->move(x0, y0, 0);

	for (int i = 0; i <= (resolution - 1); i++){
		pointerToE545->openShutter();
		pointerToE545->move(-deltaX, -deltaY, 0);
		pointerToE545->closeShutter();
		pointerToE545->move(kDeltaX, kDeltaY, 0);
		pointerToE545->move(zkDeltaX, zkDeltaX, 0);
		pointerToE545->openShutter();
		pointerToE545->move(deltaX, deltaY, 0);
		pointerToE545->closeShutter();
		pointerToE545->move(zkDeltaX, zkDeltaX, 0);
		pointerToE545->move(kDeltaX, kDeltaY, 0);
	}
	pointerToE545->openShutter();
	pointerToE545->move(-deltaX, -deltaY, 0);

	pointerToE545->closeShutter();

	pointerToE545->moveTo(pos);
}
void figures::surfaceRectangle::cutAbs()
{
	pointerToE545->setVelocity(velocity, velocity, 10);
	double delta = b / resolution;
	double pos[3];
	double deltaPhi[2];
	double R;
	double x0, y0;
	double h = 3;

	pointerToE545->getPositon(pos);

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

	pointerToE545->moveTo(x0 + pos[0], y0 + pos[1], pos[2]);

	for (int i = 0; i <= (resolution - 1); i++){
		pointerToE545->openShutter();
		pointerToE545->moveTo(-deltaX + pos[0], -deltaY + pos[1], +pos[2]);
		pointerToE545->closeShutter();
		pointerToE545->moveTo(kDeltaX + pos[0], kDeltaY + pos[1], pos[2]);
		pointerToE545->moveTo(zkDeltaX + pos[0], zkDeltaX + pos[1], pos[2]);
		pointerToE545->openShutter();
		pointerToE545->moveTo(deltaX + pos[0], deltaY + pos[1], pos[2]);
		pointerToE545->closeShutter();
		pointerToE545->moveTo(zkDeltaX + pos[0], zkDeltaX + pos[1], pos[2]);
		pointerToE545->moveTo(kDeltaX + pos[0], kDeltaY + pos[1], pos[2]);
	}
	pointerToE545->openShutter();
	pointerToE545->moveTo(-deltaX + pos[0], -deltaY + pos[1], pos[2]);

	pointerToE545->closeShutter();
	pointerToE545->moveTo(pos);

}


void figures::polygon::set(double RIn, double phi0In, int stepsIn, double velocityIn){

	velocity = velocityIn;
	R = RIn;
	phi0 = phi0In*(2 * pi) / (360.0);
	steps = stepsIn;
}
void figures::polygon::cutRel()
{
	pointerToE545->setVelocity(velocity, velocity, 10);
	double x, y, xOld, yOld;
	double deltaPhi = (2 * pi) / steps;
	double pos[3];


	xOld = R*cos(phi0);
	yOld = R*sin(phi0);

	pointerToE545->move(xOld, yOld, 0);

	pointerToE545->openShutter();
	for (int i = 1; i <= steps; i++){

		x = R*cos(phi0 + deltaPhi*i);
		y = R*sin(phi0 + deltaPhi*i);

		pointerToE545->move(x - xOld, y - yOld, 0);

		xOld = x;
		yOld = y;
	}
	pointerToE545->closeShutter();
	pointerToE545->moveTo(pos);
}
void figures::polygon::cutAbs()
{
	pointerToE545->setVelocity(velocity, velocity, 10);

	double pos[3];
	double x, y, xOld, yOld;
	double deltaPhi = (2 * pi) / steps;

	string name = "polyAbs.txt";
	fstream f;
	f << fixed;
	f << setprecision(3);

	f.open(name, fstream::out | fstream::trunc);
	f.close();
	f.open(name, fstream::out | fstream::app);

	pointerToE545->getPositon(pos);

	xOld = R*cos(phi0);
	yOld = R*sin(phi0);

	pointerToE545->moveTo(xOld + pos[0], yOld + pos[1], pos[2]);

	f << xOld + pos[0] << "\t" << yOld + pos[1] << "\t" << pos[2] << endl;

	pointerToE545->openShutter();
	for (int i = 1; i <= steps; i++){

		x = R*cos(phi0 + deltaPhi*i);
		y = R*sin(phi0 + deltaPhi*i);

		pointerToE545->moveTo(x + pos[0], y + pos[1], pos[2]);
		f << x + pos[0] << "\t" << y + pos[1] << "\t" << pos[2] << endl;
	}
	pointerToE545->closeShutter();
	pointerToE545->moveTo(pos);
	f.close();
}

