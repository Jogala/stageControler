#include "figures.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//line																												//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void figures::line::set(double lIn, double phi0In, double velocityIn, int repetionsIn){

	velocity = velocityIn;
	l = lIn;
	phi = phi0In;
	phi = (phi / 360) * 2 * pi;
	repetitions = repetionsIn;

}
void figures::line::cutRel()
{
	pointerToE545->setVelocity(velocity, velocity, 10);
	repetitions = repetitions - 1;

	double pos[3];
	double x = cos(phi)*l;
	double y = sin(phi)*l;

	pointerToE545->getPositon(pos);

	if (repetitions == 0){
		pointerToE545->openShutter();
		pointerToE545->move(x, y, 0);
		pointerToE545->closeShutter();
		pointerToE545->setVelocity(1000, 1000, 10);
		pointerToE545->moveTo(pos[0], pos[1], pos[2]);

	}
	else{

		while (repetitions >= 0){
			pointerToE545->openShutter();
			pointerToE545->move(x, y,0);
			pointerToE545->move(-x, -y, 0);
			repetitions = repetitions - 1;
		}
		pointerToE545->closeShutter();
		pointerToE545->moveTo(pos[0], pos[1], pos[2]);
	}
}
void figures::line::cutAbs()
{

	pointerToE545->setVelocity(velocity, velocity, 10);
	repetitions = repetitions - 1;

	double pos[3];
	double x = cos(phi)*l;
	double y = sin(phi)*l;

	pointerToE545->getPositon(pos);


	if (repetitions == 0){
		pointerToE545->openShutter();
		pointerToE545->moveTo(x + pos[0], y + pos[1], pos[2]);
		pointerToE545->closeShutter();
		pointerToE545->setVelocity(1000, 1000, 10);
		pointerToE545->moveTo(pos[0], pos[1], pos[2]);

	}
	else{

		while (repetitions >= 0){
			pointerToE545->openShutter();
			pointerToE545->moveTo(x + pos[0], y + pos[1], pos[2]);
			pointerToE545->moveTo(pos[0], pos[1], pos[2]);
			repetitions = repetitions - 1;
		}
		pointerToE545->closeShutter();
	}
}

void figures::line::set3D(double lIn, double phi0In,double thetaIn, double velocityIn, int repetionsIn){

	velocity = velocityIn;
	theta = thetaIn;
	l = lIn;
	phi = phi0In;
	phi = (phi / 360) * 2 * pi;
	repetitions = repetionsIn;

}
void figures::line::cutRel3D(){
	
	pointerToE545->setVelocity(velocity, velocity, velocity);
	double vec[3];
	double pos[3];
	pointerToE545->getPositon(pos);
	repetitions = repetitions - 1;

	vec[0] = l*cos(phi)*sin(theta);
	vec[1] = l*sin(phi)*sin(theta);
	vec[2] = l*cos(theta);

	if (repetitions == 0){
		pointerToE545->openShutter();
		pointerToE545->move(vec);
		pointerToE545->closeShutter();
		pointerToE545->setVelocity(1000, 1000, 10);
		pointerToE545->moveTo(pos);
	}
	else{

		while (repetitions >= 0){
			pointerToE545->openShutter();
			pointerToE545->move(vec);
			pointerToE545->move(-vec[0],-vec[1],-vec[2]);
			repetitions = repetitions - 1;
		}
		pointerToE545->closeShutter();
		pointerToE545->moveTo(pos);
	}
}
void figures::line::cutAbs3D(){

	pointerToE545->setVelocity(velocity, velocity, velocity);
	double vec[3];
	double pos[3];
	pointerToE545->getPositon(pos);
	repetitions = repetitions - 1;

	vec[0] = l*cos(phi)*sin(theta);
	vec[1] = l*sin(phi)*sin(theta);
	vec[2] = l*cos(theta);

	if (repetitions == 0){
		pointerToE545->openShutter();
		pointerToE545->moveTo(pos[0] + vec[0], pos[1] + vec[1],pos[2] + vec[2]);
		pointerToE545->closeShutter();
		pointerToE545->setVelocity(1000, 1000, 10);
		pointerToE545->moveTo(pos);
	}
	else{

		while (repetitions >= 0){
			pointerToE545->openShutter();
			pointerToE545->moveTo(pos[0] + vec[0], pos[1] + vec[1], pos[2] + vec[2]);
			pointerToE545->moveTo(pos);
			repetitions = repetitions - 1;
		}
		pointerToE545->closeShutter();
		pointerToE545->moveTo(pos);
	}

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//rectangle																											//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void figures::rectangle::leaveOrSwapAndAdjustPhi(double &phi, double &a, double &b){

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

	//phi0, sa, sb dürfen durch diese Funktion nicht geändert werden
	double sPhi = phi0;
	double sa = a;
	double sb = b;

	leaveOrSwapAndAdjustPhi(sPhi, sa, sb);
	use.degToRadByRef(sPhi);

	double pos[3];
	double deltaPhi[2];
	double R;
	double x, y, xOld, yOld;
	double deltaX;
	double deltaY;
	double factor = 10;
	double norm;
	double dummy1;
	double dummy2;

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

		pointerToE545->moveTo(xOld - deltaX, yOld - deltaY, pos[2]);	//Fahren zu Position 1
		pointerToE545->printPosition();



		cout << "as !(i%2) = " << !(i % 2) << endl;
		if (!(i % 2)){

			pointerToE545->printPosition();

			if (y <= yOld){
				//Do nothing
			}
			else{
				dummy1 = yOld;
				yOld = y;
				y = dummy1;
			}

			pointerToE545->setLimits(2, y, yOld);					//set Limits A:B
			pointerToE545->printLimits();
			pointerToE545->printPosition();

		}
		else
		{

			if (x <= xOld){
				//Do nothing
			}
			else{
				dummy1 = xOld;
				xOld = x;
				x = dummy1;
			}

			pointerToE545->setLimits(1, x, xOld);

		}


		pointerToE545->moveTo(x + deltaX, y + deltaY, pos[2]);  //Fahre zu Position 2
		pointerToE545->printPosition();
		pointerToE545->closeShutter();


	}
	pointerToE545->closeShutter();
	pointerToE545->moveTo(pos[0], pos[1], pos[2]);

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//surfaceRectangle																									//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//polygon																								//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void figures::polygon::set(double RIn, double phi0In, int stepsIn, double velocityIn){

	velocity = velocityIn;
	R = RIn;
	phi0 = phi0In*(2 * pi) / (360.0);
	steps = stepsIn;
}
void figures::polygon::set3D(double RIn, double phi0In, double rotAngleXIn, double rotAngleZIn, int stepsIn, double velocityIn){

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

bool figures::polygon::regMenuWindow(){

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
void figures::polygon::openWindowSet3D(){

	HWND hwnd;
	HWND h_text_R;

	HINSTANCE hInstance = GetModuleHandle(0);


	hwnd = CreateWindowExA(WS_EX_CLIENTEDGE, "GijSoft", "Win32 C Window application by evolution536",
		(WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX),
		CW_USEDEFAULT, CW_USEDEFAULT, 330, 350, NULL, NULL, hInstance, NULL);



	//EDIT
	int xE = 120;	//x pos
	int bE = 50;	//Breite

	//STATIC
	int xS = 20;	//x pos
	int bS = 90;	//Breite

	//Höhe 
	int hEaS = 25;

	//y position of boxes
	int top = 10;
	int deltaY = 30;

	//current Values
	int xSC = 180;	//x pos
	int bSC = 100;	//Breite


	const char *R_current = use.doubleToLPSTR(R);
	const char *phi0_current = use.doubleToLPSTR(phi0);
	const char *steps_current = use.doubleToLPSTR(steps);
	const char *velocity_current = use.doubleToLPSTR(velocity);
	const char *xRot_current = use.doubleToLPSTR(rotAngleX);
	const char *zRot_current = use.doubleToLPSTR(rotAngleZ);
	

	//Headline
	CreateWindow("STATIC", "Poly 3D ", WS_VISIBLE | WS_CHILD | SS_CENTER, xS, top, 290, hEaS,
		hwnd, NULL, hInstance, NULL);
	top += deltaY;

	CreateWindow("STATIC", "Current Values ", WS_VISIBLE | WS_CHILD | SS_RIGHT, xSC, top, bSC, hEaS,
		hwnd, NULL, hInstance, NULL);
	top += deltaY;

	//R
	CreateWindow("STATIC", "R = ", WS_VISIBLE | WS_CHILD | SS_RIGHT, xS, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);

	h_text_R = CreateWindow("EDIT", "0", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, xE, top, bE, hEaS,
		hwnd, (HMENU)ID_TEXT_POLY_R, hInstance, NULL);
	
	CreateWindow("STATIC", R_current, WS_VISIBLE | WS_CHILD | SS_RIGHT, xSC, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	
	
	top += deltaY;

	//phi0
	CreateWindow("STATIC", "phi0 = ", WS_VISIBLE | WS_CHILD | SS_RIGHT, xS, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	CreateWindow("EDIT", "0", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, xE, top, bE, hEaS,
		hwnd, (HMENU)ID_TEXT_POLY_phi0, hInstance, NULL);
	CreateWindow("STATIC", phi0_current, WS_VISIBLE | WS_CHILD | SS_RIGHT, xSC, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);

	top += deltaY;

	//xRotAngle
	CreateWindow("STATIC", "xRotAngle = ", WS_VISIBLE | WS_CHILD | SS_RIGHT, xS, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	CreateWindow("EDIT", "0", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, xE, top, bE, hEaS,
		hwnd, (HMENU)ID_TEXT_POLY_xRotWinkel, hInstance, NULL);
	CreateWindow("STATIC", xRot_current, WS_VISIBLE | WS_CHILD | SS_RIGHT, xSC, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	top += deltaY;

	//zRotAngle
	CreateWindow("STATIC", "zRotAngle = ", WS_VISIBLE | WS_CHILD | SS_RIGHT, xS, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	CreateWindow("EDIT", "0", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, xE, top, bE, hEaS,
		hwnd, (HMENU)ID_TEXT_POLY_zRotWinkel, hInstance, NULL);
	CreateWindow("STATIC", zRot_current, WS_VISIBLE | WS_CHILD | SS_RIGHT, xSC, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	top += deltaY;

	//steps
	CreateWindow("STATIC", "steps = ", WS_VISIBLE | WS_CHILD | SS_RIGHT, xS, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	CreateWindow("EDIT", "0", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, xE, top, bE, hEaS,
		hwnd, (HMENU)ID_TEXT_POLY_steps, hInstance, NULL);
	CreateWindow("STATIC", steps_current, WS_VISIBLE | WS_CHILD | SS_RIGHT, xSC, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	top += deltaY;

	//velocity
	CreateWindow("STATIC", "velocity = ", WS_VISIBLE | WS_CHILD | SS_RIGHT, xS, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	CreateWindow("EDIT", "0", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, xE, top, bE, hEaS,
		hwnd, (HMENU)ID_TEXT_POLY_velocity, hInstance, NULL);
	CreateWindow("STATIC", velocity_current, WS_VISIBLE | WS_CHILD | SS_RIGHT, xSC, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	top += deltaY;


	//BUTTON
	CreateWindowEx(0,                    /* more or ''extended'' styles */
		TEXT("BUTTON"),                         /* GUI ''class'' to create */
		TEXT("OK"),                        /* GUI caption */
		WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON | WS_TABSTOP,   /* control styles separated by | */
		10,                                     /* LEFT POSITION (Position from left) */
		top,                                     /* TOP POSITION  (Position from Top) */
		290,                                    /* WIDTH OF CONTROL */
		50,                                     /* HEIGHT OF CONTROL */
		hwnd,                                   /* Parent window handle */
		(HMENU)ID_OK_KNOPF,                        /* control''s ID for WM_COMMAND */
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

			poly_BOOL = 0;

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
		}
	}//while 


string name = "polyLastValues.txt";
fstream f;

f << fixed;
f << setprecision(3);
f.open(name, fstream::out | fstream::trunc);
f.close();
f.open(name, fstream::out | fstream::app);

f << R << endl;
f << phi0 << endl;
f << rotAngleX << endl;
f << rotAngleZ << endl;
f << steps << endl;
f << velocity << endl;
f.close();


}

void figures::polygon::cutRel()
{
	pointerToE545->setVelocity(velocity, velocity, 10);
	double x, y, xOld, yOld;
	double deltaPhi = (2 * pi) / steps;
	double pos[3];

	pointerToE545->getPositon(pos);

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

	pointerToE545->getPositon(pos);

	xOld = R*cos(phi0);
	yOld = R*sin(phi0);

	pointerToE545->moveTo(xOld + pos[0], yOld + pos[1], pos[2]);

	pointerToE545->openShutter();
	for (int i = 1; i <= steps; i++){

		x = R*cos(phi0 + deltaPhi*i);
		y = R*sin(phi0 + deltaPhi*i);

		pointerToE545->moveTo(x + pos[0], y + pos[1], pos[2]);
		/*cout << "i  = " << i << endl;
		getchar();*/
	}
	pointerToE545->closeShutter();
	pointerToE545->moveTo(pos);
}
void figures::polygon::cutAbs3D()
{
	double pos[3];
	double xOld, yOld, zOld;
	double deltaAlpha = (2 * pi) / steps;
	double vec[3];
	
	auto storagePositions = vector<vector<double>>(steps, vector<double>(3));
	
	pointerToE545->getPositon(pos);


	for (int i = 0; i < steps; i++){

		vec[0] = R*cos(phi0 + deltaAlpha*i);
		vec[1] = R*sin(phi0 + deltaAlpha*i);
		vec[2] = 0;

		use.matrixTimesVec(xRotMat, vec);
		use.matrixTimesVec(zRotMat, vec);

		storagePositions[i][0] = vec[0] + pos[0];
		storagePositions[i][1] = vec[1] + pos[1];
		storagePositions[i][2] = vec[2] + pos[2];
	}

	pointerToE545->openShutter();
	for (int i = 0; i < steps; i++){
		vec[0] = storagePositions[i][0];
		vec[1] = storagePositions[i][1];
		vec[2] = storagePositions[i][2];

		pointerToE545->moveTo(vec);
	}
	pointerToE545->closeShutter();
}

