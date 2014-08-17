#include "figures.h"
//rectangle	

void figures::rectangle::leaveOrSwapAndAdjustPhi(double &phi, double &a, double &b){

	while (phi < 0){
		phi = phi + 2*pi;
	}

	while (phi >2 * pi){

		phi = phi - 2 * pi;

	}


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
		phi = phi - pi/4.0;
	}
}
void figures::rectangle::set(double aIn, double bIn, double rotAngleZIn, double velocityIn){

	velocity = velocityIn;
	a = aIn;
	b = bIn;
	rotAngleZ = rotAngleZIn*(2 * pi) / (360.0);

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
void figures::rectangle::cutAbsLim2D()
{
	pointerToE545->setVelocity(velocity, velocity, 10);

	double sPhi = phi0;
	double sa = a;
	double sb = b;

	leaveOrSwapAndAdjustPhi(sPhi, sa, sb);

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
void figures::rectangle::cutAbs3D(){

	if ((a <= 0) || (b <= 0)){

		cout << endl;
		cout << "ERROR:" << endl;
		cout << "a <= 0 or b <= 0 are no exaptable values for a rectangle " << endl;

	}
	else{

		pointerToE545->setVelocity(velocity, velocity, velocity);

		double xRotMat[3][3];
		double zRotMat[3][3];
		double pos[3];
		double deltaPhi[2];
		double R;
		double storagePos[5][3];
		double vec[3];

		int moves = 5;

		use.setRotMatrices(xRotMat, zRotMat, rotAngleX, rotAngleZ);
		pointerToE545->getPositon(pos);

		//////////////////////////////////////////////////////////////////////////
		//		Generating the sequence of coordinates that will be visited		//
		//////////////////////////////////////////////////////////////////////////

		R = 0.5*sqrt(a*a + b*b);
		deltaPhi[0] = 2 * atan(b / a);
		deltaPhi[1] = 2 * atan(a / b);

		double deltaPhiSum = phi0 - deltaPhi[0] / 2.0;

		//A
		//##################################
		vec[0] = R*cos(deltaPhiSum);
		vec[1] = R*sin(deltaPhiSum);
		vec[2] = 0;

		use.matrixTimesVec(xRotMat, vec);
		use.matrixTimesVec(zRotMat, vec);

		storagePos[0][0] = vec[0] + pos[0];
		storagePos[0][1] = vec[1] + pos[1];
		storagePos[0][2] = vec[2] + pos[2];
		//##################################

		//B, C, D, A 
		for (int i = 1; i < moves; i++){

			deltaPhiSum = deltaPhiSum + deltaPhi[((i + 1) % 2)];

			vec[0] = R*cos(deltaPhiSum);
			vec[1] = R*sin(deltaPhiSum);
			vec[2] = 0;

			use.matrixTimesVec(xRotMat, vec);
			use.matrixTimesVec(zRotMat, vec);

			storagePos[i][0] = vec[0] + pos[0];
			storagePos[i][1] = vec[1] + pos[1];
			storagePos[i][2] = vec[2] + pos[2];
		}

		//////////////////////////////////////////////////////
		//		Write sequence to file for controle			//
		//////////////////////////////////////////////////////

		use.writeCoordToFile("rec3DAbs.txt", storagePos, moves);


		//////////////////////////////////////////
		//		Actual cutting procedure 		//
		//////////////////////////////////////////

		//A
		pointerToE545->moveTo(storagePos[0][0], storagePos[0][1], storagePos[0][2]);
		pointerToE545->openShutter();
		//B, C, D, A
		for (int i = 1; i < moves; i++){

			pointerToE545->moveTo(storagePos[i][0], storagePos[i][1], storagePos[i][2]);

		}
		pointerToE545->closeShutter();

		pointerToE545->moveTo(pos);

	}
}

bool figures::rectangle::regMenuWindow(){

	HINSTANCE hInstance = GetModuleHandle(0);
	WNDCLASSEX wcRec;

	wcRec.cbSize = sizeof(WNDCLASSEX);
	wcRec.style = 0;
	wcRec.lpfnWndProc = WndProcNewRectangle3D;
	wcRec.cbClsExtra = 0;
	wcRec.cbWndExtra = 0;
	wcRec.hInstance = hInstance;
	wcRec.hIcon = NULL;
	wcRec.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wcRec.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcRec.lpszMenuName = NULL;
	wcRec.lpszClassName = "rectangle";
	wcRec.hIconSm = NULL;

	if (!RegisterClassEx(&wcRec))
	{
		cout << "RegisterClassEx wcRec failed" << endl;
		return 0;
	}

}
void figures::rectangle::openWindowSet3D(){

	HWND hwnd;
	HWND h_text_a;

	HINSTANCE hInstance = GetModuleHandle(0);

	hwnd = CreateWindowExA(WS_EX_CLIENTEDGE, "rectangle", "",
		(WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX),
		CW_USEDEFAULT, CW_USEDEFAULT, 500, 350, NULL, NULL, hInstance, NULL);

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

	double rotAngleXInDeg = (rotAngleX / (2 * pi))*(360);
	double rotAngleZInDeg = (rotAngleZ / (2 * pi))*(360);
	double phi0InDeg = (phi0 / (2 * pi))*(360);

	const string sA = use.numberToString(a);
	const string sB = use.numberToString(b);
	const string sPhi0 = use.numberToString(phi0InDeg);
	const string sRotAngleX = use.numberToString(rotAngleXInDeg);
	const string sRotAngleZ = use.numberToString(rotAngleZInDeg);
	const string sVelocity = use.numberToString(velocity);


	//Headline
	CreateWindow("STATIC", "Rectangle 3D ", WS_VISIBLE | WS_CHILD | SS_CENTER, xS, top, 290, hEaS,
		hwnd, NULL, hInstance, NULL);
	top += deltaY;

	CreateWindow("STATIC", "currently", WS_VISIBLE | WS_CHILD | SS_CENTER, xSC, top, bSC, hEaS,
		hwnd, NULL, hInstance, NULL);
	CreateWindow("STATIC",

		"For cutting in the x-y plane\nleave xRotAngle and zRotAngle = 0\n\nFor cutting perpendicular to the x - y plane\nleave phi0 = 0, \nand chose xRotAngle = 90"


		, WS_VISIBLE | WS_CHILD | SS_LEFT, xSC + bSC + 10, top, 180, 205,
		hwnd, NULL, hInstance, NULL);
	top += deltaY;

	//a
	CreateWindow("STATIC", "a = ", WS_VISIBLE | WS_CHILD | SS_RIGHT, xS, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);

	h_text_a = CreateWindow("EDIT", sA.c_str(), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, xE, top, bE, hEaS,
		hwnd, (HMENU)ID_TEXT_REC_a, hInstance, NULL);

	CreateWindow("STATIC", sA.c_str(), WS_VISIBLE | WS_CHILD | SS_RIGHT, xSC, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);


	top += deltaY;

	//b
	CreateWindow("STATIC", "b = ", WS_VISIBLE | WS_CHILD | SS_RIGHT, xS, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	CreateWindow("EDIT", sB.c_str(), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, xE, top, bE, hEaS,
		hwnd, (HMENU)ID_TEXT_REC_b, hInstance, NULL);
	CreateWindow("STATIC", sB.c_str(), WS_VISIBLE | WS_CHILD | SS_RIGHT, xSC, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);

	top += deltaY;

	//phi0
	CreateWindow("STATIC", "phi0 = ", WS_VISIBLE | WS_CHILD | SS_RIGHT, xS, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	CreateWindow("EDIT", sPhi0.c_str(), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, xE, top, bE, hEaS,
		hwnd, (HMENU)ID_TEXT_REC_phi0, hInstance, NULL);
	CreateWindow("STATIC", sPhi0.c_str(), WS_VISIBLE | WS_CHILD | SS_RIGHT, xSC, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	top += deltaY;

	//xRotAngle
	CreateWindow("STATIC", "xRotAngle = ", WS_VISIBLE | WS_CHILD | SS_RIGHT, xS, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	CreateWindow("EDIT", sRotAngleX.c_str(), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, xE, top, bE, hEaS,
		hwnd, (HMENU)ID_TEXT_REC_xRotWinkel, hInstance, NULL);
	CreateWindow("STATIC", sRotAngleX.c_str(), WS_VISIBLE | WS_CHILD | SS_RIGHT, xSC, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	top += deltaY;

	//zRotAngle
	CreateWindow("STATIC", "zRotAngle = ", WS_VISIBLE | WS_CHILD | SS_RIGHT, xS, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	CreateWindow("EDIT", sRotAngleZ.c_str(), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, xE, top, bE, hEaS,
		hwnd, (HMENU)ID_TEXT_REC_zRotWinkel, hInstance, NULL);
	CreateWindow("STATIC", sRotAngleZ.c_str(), WS_VISIBLE | WS_CHILD | SS_RIGHT, xSC, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	top += deltaY;

	//velocity
	CreateWindow("STATIC", "velocity = ", WS_VISIBLE | WS_CHILD | SS_RIGHT, xS, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	CreateWindow("EDIT", sVelocity.c_str(), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, xE, top, bE, hEaS,
		hwnd, (HMENU)ID_TEXT_REC_velocity, hInstance, NULL);
	CreateWindow("STATIC", sVelocity.c_str(), WS_VISIBLE | WS_CHILD | SS_RIGHT, xSC, top, bS, hEaS,
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
		(HMENU)ID_OK_KNOPF_REC,                        /* control''s ID for WM_COMMAND */
		hInstance,                                /* application instance */
		NULL);


	//Show the window including all controls.
	ShowWindow(hwnd, 5);
	UpdateWindow(hwnd);
	SetForegroundWindow(hwnd);

	//set h_text_R on focus and mark text, such that user can start typing new values immidiately
	SetFocus(h_text_a);
	SendDlgItemMessage(hwnd, ID_TEXT_REC_a, EM_SETSEL, 0, -1);


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

		if (rec_BOOL)
		{
			//a
			////////////////////////////////////////////////////
			use.assignValueToMember(G_Text_Rec_a, a, "a");

			//b
			////////////////////////////////////////////////////
			use.assignValueToMember(G_Text_Rec_b, b, "b");

			//rotangleX
			////////////////////////////////////////////////////
			use.assignValueToMember(G_Text_Rec_xRotWinkel, rotAngleX, "rotanglex");
			rotAngleX = (rotAngleX / 360)*(2 * pi);
			//rotangleZ
			////////////////////////////////////////////////////
			use.assignValueToMember(G_Text_Rec_zRotWinkel, rotAngleZ, "rotAngleZ");
			rotAngleZ = (rotAngleZ / 360)*(2 * pi);
			//veclotiy
			////////////////////////////////////////////////////
			use.assignValueToMember(G_Text_Rec_velocity, velocity, "velocity");
			//phi0
			////////////////////////////////////////////////////
			use.assignValueToMember(G_Text_Rec_phi0, phi0, "phi0");
			phi0 = (phi0 / 360)*(2 * pi);
			//Export Values s.t. they can be loaded the next time the program starts
			string name = "recLastValues.txt";
			fstream f;

			f << fixed;
			f << setprecision(3);
			f.open(name, fstream::out | fstream::trunc);
			f.close();
			f.open(name, fstream::out | fstream::app);

			f << a << endl;
			f << b << endl;
			f << phi0 << endl;
			f << rotAngleX << endl;
			f << rotAngleZ << endl;
			f << velocity << endl;
			f.close();

			rec_BOOL = 0;
		}
	}//while 




}
void figures::rectangle::loadValuesFromTextFile(){

	cout << "Old Values Rectangle" << endl;
	fstream myReadFile;
	myReadFile.open("recLastValues.txt");
	double x;
	int i = 0;
	if (myReadFile.is_open()) {
		while (i<5) {

			if (i == 0){
				myReadFile >> a;
				cout << a << endl;
				i++;
			}

			if (i == 1){
				myReadFile >> b;
				cout << b << endl;
				i++;
			}

			if (i == 2){
				myReadFile >> phi0;
				cout << phi0 << endl;
				i++;
			}

			if (i == 3){
				myReadFile >> rotAngleX;
				cout << rotAngleX << endl;
				i++;
			}
			if (i == 4){
				myReadFile >> rotAngleZ;
				cout << rotAngleZ << endl;
				i++;
			}
			if (i == 5){
				myReadFile >> velocity;
				cout << velocity << endl;
				i++;
			}
		}
	}
	myReadFile.close();

}
void figures::rectangle::printMemberVariables(){

	cout << "a = " << "\t" << a << endl;
	cout << "b = " << "\t" << a << endl;
	cout << "xRot = " << "\t" << rotAngleX << endl;
	cout << "xRot = " << "\t" << rotAngleZ << endl;
	cout << "velocity = " << "\t" << rotAngleZ << endl;

}
