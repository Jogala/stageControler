#include "figuresWriteCoordToFile.h"

void figuresWriteCoordToFile::line::set3D(double lIn, double phiIn ,double thetaIn, double  velocityIn, int repetionsIn){

	velocity = velocityIn;
	l = lIn;
	phi = phiIn;
	phi = (phi / 360) * 2 * pi;

	repetitions = repetionsIn;
	use.setRotMatrices(xRotMat, zRotMat, phi, -theta);
}
void figuresWriteCoordToFile::line::cutRel3D(){

	double vec[3];
	vec[0] = l*cos(phi)*sin(theta);
	vec[1] = l*sin(phi)*sin(theta);
	vec[2] = l*cos(theta);

	string name = "line3D.txt";
	fstream f;
	f << fixed;
	f << setprecision(3);

	f.open(name, fstream::out | fstream::trunc);
	f.close();
	f.open(name, fstream::out | fstream::app);

	f << vec[0] << "\t" << vec[1] << "\t" << vec[2] << endl;
	


	f.close();

}
void figuresWriteCoordToFile::line::cutAbs3D(){}

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
void figuresWriteCoordToFile::polygon::set3D(double RIn, double phi0In, double rotAngleXIn, double rotAngleZIn, int stepsIn, double velocityIn){

	rotAngleX = rotAngleXIn;
	rotAngleZ = rotAngleZIn;

	velocity = velocityIn;
	R = RIn;
	phi0 = phi0In*(2 * pi) / (360.0);
	double tempRotAngleX = rotAngleX*(2 * pi) / (360.0);
	double tempRotAngleZ = rotAngleZ*(2 * pi) / (360.0);
	steps = stepsIn;

	use.setRotMatrices(xRotMat, zRotMat, tempRotAngleX, tempRotAngleZ);


}
void figuresWriteCoordToFile::polygon::cutAbs3D()
{
	double pos[3];
	double xOld, yOld, zOld;
	double vec[3];
	double x, y, z;
	double deltaAlpha = (2 * pi) / steps;

	string name = "poly3D.txt";
	fstream f;
	f << fixed;
	f << setprecision(3);

	f.open(name, fstream::out | fstream::trunc);
	f.close();
	f.open(name, fstream::out | fstream::app);

	pos[0] = 100;
	pos[1] = 100;
	pos[2] = 100;

	vec[0] = R*cos(phi0);
	vec[1] = R*sin(phi0);
	vec[2] = 0;

	use.matrixTimesVec(xRotMat, vec);
	use.matrixTimesVec(zRotMat, vec);

	f<<vec[0] + pos[0]<<"\t"<< vec[1]+ pos[1]<<"\t"<< vec[2]+pos[2] <<endl;

	for (int i = 1; i <= steps; i++){

		x = R*cos(phi0 + deltaAlpha*i);
		y = R*sin(phi0 + deltaAlpha*i);

		vec[0] = x;
		vec[1] = y;
		vec[2] = 0;

		use.matrixTimesVec(xRotMat, vec);
		use.matrixTimesVec(zRotMat, vec);

		f << vec[0] + pos[0] << "\t" << vec[1] + pos[1] << "\t" << vec[2] + pos[2] << endl;
	}

	
	f.close();
}

bool  figuresWriteCoordToFile::polygon::regMenuWindow(){

	HINSTANCE hInstance = GetModuleHandle(0);
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProcNewPoly3D;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "GijSoft";
	wc.hIconSm = NULL;

	// This function actually registers the window class. If the information specified in the 'wc' struct is correct,
	// the window class should be created and no error is returned.
	if (!RegisterClassEx(&wc))
	{
		cout << "RegisterClassEx failed" << endl;
		return 0;
	}

}
void  figuresWriteCoordToFile::polygon::openWindowSet3D(){
	
	HWND button, hwnd;

	HWND h_text_R;
	HWND h_text_phi0;
	HWND h_text_velocity;
	HWND h_text_steps;

	HINSTANCE hInstance = GetModuleHandle(0);


	hwnd = CreateWindowExA(WS_EX_CLIENTEDGE, "GijSoft", "Win32 C Window application by evolution536",
		(WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX),
		CW_USEDEFAULT, CW_USEDEFAULT, 250, 300, NULL, NULL, hInstance, NULL);

	// This function creates the button that is displayed on the window. It takes almost the same parameter types as the function
	// that created the window. A thing to note here though, is BS_DEFPUSHBUTTON, and BUTTON as window class, which is an existing one.

	//EDIT
	int xE = 120;	//x pos
	int bE = 50;	//Breite

	//STATIC
	int xS = 20;	//x pos
	int bS = 90;	//Breite
	
	//Höhe EDIT and STATIC
	int hEaS = 25;

	//y position of boxes
	int top= 10;
	int deltaY=30;

	//R
	CreateWindow("STATIC", "R = ", WS_VISIBLE | WS_CHILD | SS_RIGHT, xS, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	h_text_R = CreateWindow("EDIT", "0", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, xE, top, bE, hEaS,
		hwnd,(HMENU)ID_TEXT_POLY_R, hInstance, NULL);
	top += deltaY;

	//phi0
	CreateWindow("STATIC", "phi0 = ", WS_VISIBLE | WS_CHILD | SS_RIGHT, xS, top, bS, hEaS,
		hwnd,NULL, hInstance, NULL);
	CreateWindow("EDIT", "0", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, xE, top, bE, hEaS,
		hwnd,(HMENU)ID_TEXT_POLY_phi0, hInstance, NULL);
	top += deltaY;

	//xRotAngle
	CreateWindow("STATIC", "xRotAngle = ", WS_VISIBLE | WS_CHILD | SS_RIGHT, xS, top, bS, hEaS,
		hwnd,NULL, hInstance, NULL);
	CreateWindow("EDIT", "0", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, xE, top, bE, hEaS,
		hwnd,	(HMENU)ID_TEXT_POLY_xRotWinkel, hInstance, NULL);
	top += deltaY;

	//zRotAngle
	CreateWindow("STATIC", "zRotAngle = ", WS_VISIBLE | WS_CHILD | SS_RIGHT, xS, top, bS, hEaS,
		hwnd,NULL, hInstance, NULL);
	CreateWindow("EDIT", "0", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, xE, top, bE, hEaS,
		hwnd,(HMENU)ID_TEXT_POLY_zRotWinkel, hInstance, NULL);
	top += deltaY;

	//steps
	CreateWindow("STATIC", "steps = ", WS_VISIBLE | WS_CHILD | SS_RIGHT, xS, top, bS, hEaS,
		hwnd,NULL, hInstance, NULL);
	CreateWindow("EDIT", "0", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, xE, top, bE, hEaS,
		hwnd,(HMENU)ID_TEXT_POLY_steps, hInstance, NULL);
	top += deltaY;

	//velocity
	CreateWindow("STATIC", "velocity = ", WS_VISIBLE | WS_CHILD | SS_RIGHT, xS, top, bS, hEaS,
		hwnd,NULL, hInstance, NULL);
	CreateWindow("EDIT", "0", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, xE, top, bE, hEaS,
		hwnd,(HMENU)ID_TEXT_POLY_velocity, hInstance, NULL);
	top += deltaY;

	button = CreateWindowEx(0,                    /* more or ''extended'' styles */
		TEXT("BUTTON"),                         /* GUI ''class'' to create */
		TEXT("APPLAY"),                        /* GUI caption */
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON | WS_TABSTOP,   /* control styles separated by | */
		10,                                     /* LEFT POSITION (Position from left) */
		top,                                     /* TOP POSITION  (Position from Top) */
		150,                                    /* WIDTH OF CONTROL */
		50,                                     /* HEIGHT OF CONTROL */
		hwnd,                                   /* Parent window handle */
		(HMENU)ID_OK_KNOPF_POLY,                        /* control''s ID for WM_COMMAND */
		hInstance,                                /* application instance */
		NULL);
	

	//Show the window including all controls.
	ShowWindow(hwnd, 5);
	UpdateWindow(hwnd);

	//set h_text_R on focus and mark text, such that user can start typing new values immidiately
	SetFocus(h_text_R);
	SendDlgItemMessage(hwnd, ID_TEXT_POLY_R, EM_SETSEL, 0, -1);

	
	MSG Msg;
	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{

		if (IsDialogMessage(hwnd, &Msg)) {
			/* Already handled by dialog manager */
		}
		else {

			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}

			string myString;
			stringstream ss;
			
			if (poly_BOOL)
			{
				//R
				////////////////////////////////////////////////////
				myString = G_Text_Poly_R;
				ss.str(myString);
				if (!(ss >> R)){
					cout << "no new value set for R" << endl;
				}
				else{
					cout << "R = " << R << endl;
				}
				ss.str("");
				ss.clear();

				//phi0
				////////////////////////////////////////////////////
				myString = G_Text_Poly_phi0;
				ss.str(myString);
				if (!(ss >> phi0)){
					cout << "no new value set for phi0" << endl;
				}
				else{
					cout << "phi0 = " << phi0 << endl;
				}
				ss.str("");
				ss.clear();

				//xRotAngle
				////////////////////////////////////////////////////
				myString = G_Text_Poly_xRotWinkel;
				ss.str(myString);
				if (!(ss >> rotAngleX)){
					cout << "no new value set for steps" << endl;
				}
				else{
					cout << "rotAngleX = " << rotAngleX << endl;
				}
				ss.str("");
				ss.clear();

				//zRotAngle
				////////////////////////////////////////////////////
				myString = G_Text_Poly_zRotWinkel;
				ss.str(myString);
				if (!(ss >> rotAngleZ)){
					cout << "no new value set for steps" << endl;
				}
				else{
					cout << "rotAngleZ = " << rotAngleZ << endl;
				}
				ss.str("");
				ss.clear();

				//steps
				////////////////////////////////////////////////////
				myString = G_Text_Poly_steps;
				ss.str(myString);
				if (!(ss >> steps)){
					cout << "no new value set for steps" << endl;
				}
				else{
					cout << "steps = " << steps << endl;
				}
				ss.str("");
				ss.clear();

				//velocity
				////////////////////////////////////////////////////
				myString = G_Text_Poly_velocity;
				ss.str(myString);
				if (!(ss >> velocity)){
					cout << "no new value set for velocity" << endl;
				}
				else{
					cout << "velocity = " << velocity << endl;

				}
				ss.str("");
				ss.clear();

				
			
			poly_BOOL = 0;

		}
	}//while 
}

