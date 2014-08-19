#include "figures.h"

//polygon	

void figures::polygon::loadValuesFromTextFile(){

	cout << "Old Values Poly" << endl;
	fstream myReadFile;
	myReadFile.open("polyLastValues.txt");

	int i = 0;
	if (myReadFile.is_open()) {
		while (i < 6) {

			if (i == 0){
				myReadFile >> itsR;
				cout << itsR << endl;
				i++;
			}

			if (i == 1){
				myReadFile >> phi0;
				cout << phi0 << endl;
				i++;
			}
			if (i == 2){
				myReadFile >> rotAngleX;
				cout << rotAngleX << endl;
				i++;
			}
			if (i == 3){
				myReadFile >> rotAngleZ;
				cout << rotAngleZ << endl;
				i++;
			}
			if (i == 4){
				myReadFile >> steps;
				cout << steps << endl;
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
void figures::polygon::set(double RIn, double phi0In, int stepsIn, double velocityIn){

	velocity = velocityIn;
	itsR = RIn;
	phi0 = phi0In*(2 * pi) / (360.0);
	steps = stepsIn;
}
void figures::polygon::set3D(double RIn, double phi0In, double rotAngleXIn, double rotAngleZIn, int stepsIn, double velocityIn){

	rotAngleX = rotAngleXIn;
	rotAngleZ = rotAngleZIn;

	velocity = velocityIn;
	itsR = RIn;
	phi0 = phi0In*(2 * pi) / (360.0);
	double tempRotAngleX = rotAngleX*(2 * pi) / (360.0);
	double tempRotAngleZ = rotAngleZ*(2 * pi) / (360.0);
	steps = stepsIn;

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
	wc.lpszClassName = "polygon";
	wc.hIconSm = NULL;

	// This function actually registers the window class. If the information specified in the 'wc' struct is correct,
	// the window class should be created and no error is returned.
	if (!RegisterClassEx(&wc))
	{
		cout << "RegisterClassEx failed" << endl;
		return 0;
	}
	else{
		return 1;
	}

}
void figures::polygon::openWindowSet3D(){

	HWND hwnd;
	HWND h_text_R;

	HINSTANCE hInstance = GetModuleHandle(0);

	hwnd = CreateWindowExA(WS_EX_CLIENTEDGE, "polygon", "",
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

	double rotAngleXInDeg = (rotAngleX / (2 * pi))*(360);
	double rotAngleZInDeg = (rotAngleZ / (2 * pi))*(360);
	double phi0InDeg = (rotAngleZ / (2 * pi))*(360);

	const string sR = use.numberToString(itsR);
	const string sPhi0 = use.numberToString(phi0InDeg);
	const string sSteps = use.numberToString(steps);
	const string sRotAngleX = use.numberToString(rotAngleXInDeg);
	const string sRotAngleZ = use.numberToString(rotAngleZInDeg);
	const string sVelocity = use.numberToString(velocity);


	//Headline
	CreateWindow("STATIC", "Poly 3D ", WS_VISIBLE | WS_CHILD | SS_CENTER, xS, top, 290, hEaS,
		hwnd, NULL, hInstance, NULL);
	top += deltaY;

	CreateWindow("STATIC", "currently", WS_VISIBLE | WS_CHILD | SS_RIGHT, xSC, top, bSC, hEaS,
		hwnd, NULL, hInstance, NULL);
	top += deltaY;

	//R
	CreateWindow("STATIC", "R = ", WS_VISIBLE | WS_CHILD | SS_RIGHT, xS, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);

	h_text_R = CreateWindow("EDIT", sR.c_str(), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, xE, top, bE, hEaS,
		hwnd, (HMENU)ID_TEXT_POLY_R, hInstance, NULL);

	CreateWindow("STATIC", sR.c_str(), WS_VISIBLE | WS_CHILD | SS_RIGHT, xSC, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);


	top += deltaY;

	//phi0
	CreateWindow("STATIC", "phi0 = ", WS_VISIBLE | WS_CHILD | SS_RIGHT, xS, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	CreateWindow("EDIT", sPhi0.c_str(), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, xE, top, bE, hEaS,
		hwnd, (HMENU)ID_TEXT_POLY_phi0, hInstance, NULL);
	CreateWindow("STATIC", sPhi0.c_str(), WS_VISIBLE | WS_CHILD | SS_RIGHT, xSC, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);

	top += deltaY;

	//xRotAngle
	CreateWindow("STATIC", "xRotAngle = ", WS_VISIBLE | WS_CHILD | SS_RIGHT, xS, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	CreateWindow("EDIT", sRotAngleX.c_str(), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, xE, top, bE, hEaS,
		hwnd, (HMENU)ID_TEXT_POLY_xRotWinkel, hInstance, NULL);
	CreateWindow("STATIC", sRotAngleX.c_str(), WS_VISIBLE | WS_CHILD | SS_RIGHT, xSC, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	top += deltaY;

	//zRotAngle
	CreateWindow("STATIC", "zRotAngle = ", WS_VISIBLE | WS_CHILD | SS_RIGHT, xS, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	CreateWindow("EDIT", sRotAngleZ.c_str(), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, xE, top, bE, hEaS,
		hwnd, (HMENU)ID_TEXT_POLY_zRotWinkel, hInstance, NULL);
	CreateWindow("STATIC", sRotAngleZ.c_str(), WS_VISIBLE | WS_CHILD | SS_RIGHT, xSC, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	top += deltaY;

	//steps
	CreateWindow("STATIC", "steps = ", WS_VISIBLE | WS_CHILD | SS_RIGHT, xS, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	CreateWindow("EDIT", sSteps.c_str(), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, xE, top, bE, hEaS,
		hwnd, (HMENU)ID_TEXT_POLY_steps, hInstance, NULL);
	CreateWindow("STATIC", sSteps.c_str(), WS_VISIBLE | WS_CHILD | SS_RIGHT, xSC, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	top += deltaY;

	//velocity
	CreateWindow("STATIC", "velocity = ", WS_VISIBLE | WS_CHILD | SS_RIGHT, xS, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	CreateWindow("EDIT", sVelocity.c_str(), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, xE, top, bE, hEaS,
		hwnd, (HMENU)ID_TEXT_POLY_velocity, hInstance, NULL);
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
		(HMENU)ID_OK_KNOPF_POLY,                        /* control''s ID for WM_COMMAND */
		hInstance,                                /* application instance */
		NULL);


	//Show the window including all controls.
	ShowWindow(hwnd, 5);
	UpdateWindow(hwnd);
	SetForegroundWindow(hwnd);

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

		if (poly_BOOL)
		{
			//R
			////////////////////////////////////////////////////
			use.assignValueToMember(G_Text_Poly_R, itsR, "R");

			//phi0
			////////////////////////////////////////////////////
			use.assignValueToMember(G_Text_Poly_phi0, phi0, "phi0");
			phi0 = (phi0 / 360)*(2 * pi);
			//steps
			////////////////////////////////////////////////////
			use.assignValueToMember(G_Text_Poly_steps, steps, "steps");

			//rotangleX
			////////////////////////////////////////////////////
			use.assignValueToMember(G_Text_Poly_xRotWinkel, rotAngleX, "rotanglex");

			while (rotAngleX < 0){
				rotAngleX = rotAngleX + 360;
			}

			while (rotAngleX> 360){
				rotAngleX = rotAngleX - 360;
			}

			rotAngleX = (rotAngleX / 360)*(2 * pi);

			use.assignValueToMember(G_Text_Poly_zRotWinkel, rotAngleZ, "rotAngleZ");

			while (rotAngleX < 0){
				rotAngleZ = rotAngleZ + 360;
			}

			while (rotAngleX> 360){
				rotAngleZ = rotAngleZ - 360;
			}

			rotAngleZ = (rotAngleZ / 360)*(2 * pi);

			//veclotiy
			////////////////////////////////////////////////////
			use.assignValueToMember(G_Text_Poly_velocity, velocity, "velocity");

			//Export Values s.t. they can be loaded the next time the program starts
			string name = "polyLastValues.txt";
			fstream f;

			f << fixed;
			f << setprecision(3);
			f.open(name, fstream::out | fstream::trunc);
			f.close();
			f.open(name, fstream::out | fstream::app);

			f << itsR << endl;
			f << phi0 << endl;
			f << rotAngleX << endl;
			f << rotAngleZ << endl;
			f << steps << endl;
			f << velocity << endl;
			f.close();

			poly_BOOL = 0;
		}
	}//while 





}

void figures::polygon::cutRel()
{
	double R = itsR;
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
	double R = itsR;
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

	double R = itsR;
	pointerToE545->setVelocity(velocity, velocity, velocity);

	double pos[3];
	pointerToE545->getPositon(pos);

	double deltaAlpha = (2 * pi) / steps;
	double vec[3];
	double xRotMat[3][3];
	double zRotMat[3][3];

	use.setRotMatrices(xRotMat, zRotMat, rotAngleX, rotAngleZ);
	auto storagePos = vector<vector<double>>(steps + 1, vector<double>(3));




	//////////////////////////////////////////
	//		Generating the coordinates		//
	//////////////////////////////////////////
	for (int i = 0; i <= steps; i++){

		vec[0] = R*cos(phi0 + deltaAlpha*i);
		vec[1] = R*sin(phi0 + deltaAlpha*i);
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

	use.writeCoordToFile("poly3DAbs.txt", storagePos, steps + 1);

	//////////////////////////////////////////
	//		Actual cutting procedure 		//
	//////////////////////////////////////////

	for (int i = 0; i <= steps; i++){

		vec[0] = storagePos[i][0];
		vec[1] = storagePos[i][1];
		vec[2] = storagePos[i][2];
		pointerToE545->moveTo(vec);

		if (i == 0){
			pointerToE545->openShutter();
		}
	}
	pointerToE545->closeShutter();

	//Move Back to center
	pointerToE545->moveTo(pos);
}

void figures::polygon::cutAbsMacro3D(){

	double R = itsR;
	double pos[3];
	pointerToE545->getPositon(pos);

	double deltaAlpha = (2 * pi) / steps;
	double vec[3];
	auto storPos = vector<vector<double>>(steps + 1, vector<double>(3));

	double delay = 1000 * (sin(deltaAlpha / 2) * 2 * R*delayFactor) / velocity;
	double delayGoingBackToPos;

	string macroName = "macroPoly";
	string nameFile = "macroPoly.txt";

	double xRotMat[3][3];
	double zRotMat[3][3];
	use.setRotMatrices(xRotMat, zRotMat, rotAngleX, rotAngleZ);

	//////////////////////////////////////////
	//		Generating the coordinates		//
	//////////////////////////////////////////
	for (int i = 0; i < steps+1; i++){

		vec[0] = R*cos(deltaAlpha*i + pi / 2);
		vec[1] = R*sin(deltaAlpha*i + pi / 2);
		vec[2] = 0;

		use.matrixTimesVec(xRotMat, vec);
		use.matrixTimesVec(zRotMat, vec);

		storPos[i][0] = vec[0] + pos[0];
		storPos[i][1] = vec[1] + pos[1];
		storPos[i][2] = vec[2] + pos[2];
	}

	fstream fc;
	fc << fixed;
	fc << setprecision(5);
	fc.open(nameFile, fstream::out | fstream::trunc);
	fc.close();
	fc.open(nameFile, fstream::out | fstream::app);
	//Write sequence to file for controle			
	//###################################################################
	for (int i = 0; i < steps + 1; i++){
		for (int j = 0; j < 3; j++){

			fc << storPos[i][j] << endl;

		}
	}
	use.writeCoordToFile("cutAbsMacro3D_Coord.txt", storPos, steps + 1);
	//#####################################################################
	fc.close();
	cout << "coordinates written to file:" << "cutAbsMacro3D_Coord.txt" << endl;

	//////////////////////////////////////////
	//		Actual cutting procedure 		//
	//////////////////////////////////////////

	fstream f;
	f << fixed;
	f << setprecision(5);
	f.open(nameFile, fstream::out | fstream::trunc);
	f.close();
	f.open(nameFile, fstream::out | fstream::app);

	f << "MAC BEG " << macroName << endl;
	f << "VEL A " << velocity << " B " << velocity << " C " << velocity << endl;
	//Open Shutter
	for (int i = 0; i < steps+1; i++){
		f << "MOV A " << storPos[i][0] << " B " << storPos[i][1] << " C " << storPos[i][2] << endl;
		

		if (i == 0){
			f << "DEL " << (R / velocity) * 1000 * 2 << endl;
			f << pointerToE545->setLimitsMacro(1, 0, 200, 0, 0);
		}
		else{
			f << "DEL " << delay << endl;
		}
	}
	//Close Shutter
	f << pointerToE545->setLimitsMacro(1, 0, 0, 0, 200);
	//Geh zurück
	f << "DEL " << endl;
	f << "MAC END" << endl;
	f.close();

	cout << "Macro written to file:" << nameFile << endl;

	pointerToE545->sendMacros(nameFile);
	cout << "START MACRO" << endl;
	pointerToE545->closeShutter();
	pointerToE545->startMacroAndWaitWhileRunning(macroName);
	pointerToE545->moveTo(pos);

}
void figures::polygon::cutAbsMacroSpiral3D(){

	int nOld = 0;
	double R = itsR;
	int sectors = 4;
	double factorR = 0.5;
	double deltaR = (R*factorR) / sectors;
	cout << "deltaR = "<<deltaR << endl;
	int stepsPerSector = steps / sectors;
	cout << "stepsPerSector = " << stepsPerSector << endl;
	double pos[3];

	pos[0] = 0;
	pos[1] = 0;
	pos[2] = 0;

	//pointerToE545->getPositon(pos);

	double deltaAlpha = (2 * pi) / steps;
	double vec[3];
	auto storPos = vector<vector<double>>(steps + 1, vector<double>(3));

	double delay = 1000 * (sin(deltaAlpha / 2) * 2 * R*delayFactor) / velocity;
	double delayGoingBackToPos;

	string macroName = "macroSpiral";
	string nameFile = "macroSpiral.txt";

	double xRotMat[3][3];
	double zRotMat[3][3];
	use.setRotMatrices(xRotMat, zRotMat, rotAngleX, rotAngleZ);

	//////////////////////////////////////////
	//		Generating the coordinates		//
	//////////////////////////////////////////
	int n = 0;
	for (int i = 0; i < steps + 1; i++){


		vec[0] = R*cos(deltaAlpha*i + pi / 2);
		vec[1] = R*sin(deltaAlpha*i + pi / 2);
		vec[2] = 0;

		use.matrixTimesVec(xRotMat, vec);
		use.matrixTimesVec(zRotMat, vec);

		storPos[i][0] = vec[0] + pos[0];
		storPos[i][1] = vec[1] + pos[1];
		storPos[i][2] = vec[2] + pos[2];

		n = i/stepsPerSector;
		cout << "n = " <<n << endl;
		if (nOld!=n){
			R = R - deltaR;
		}
		nOld = n;
	}
	
	int color=1;
	fstream fc;
	fc << fixed;
	fc << setprecision(5);
	fc.open("cutAbsMacroSpiral3D_Coord.txt", fstream::out | fstream::trunc);
	fc.close();
	fc.open("cutAbsMacroSpiral3D_Coord.txt", fstream::out | fstream::app);
	//Write sequence to file for controle			
	//###################################################################
	n = 0;
	nOld = 0;
	for (int i = 0; i < steps + 1; i++){
		
		n = i/stepsPerSector;
		
		if (nOld!=n){
			//Close Shutter
			color = 0;
		}
		for (int j = 0; j < 3; j++){
			
			fc << storPos[i][j]<<"\t";
		}
		
		fc << color << endl;
		if (nOld != n){
			//Open Shutter
			color = 1;
		}
		nOld = n;
	}
	//#####################################################################
	fc.close();


	//////////////////////////////////////////
	//		Actual cutting procedure 		//
	//////////////////////////////////////////

	fstream f;
	f << fixed;
	f << setprecision(5);
	f.open(nameFile, fstream::out | fstream::trunc);
	f.close();
	f.open(nameFile, fstream::out | fstream::app);

	f << "MAC BEG " << macroName << endl;
	f << "VEL A " << velocity << " B " << velocity << " C " << velocity << endl;
	//Open Shutter
	n = 0;
	nOld = 0;
	for (int i = 0; i < steps + 1; i++){
		
		n = i/stepsPerSector;
		if (nOld!=n){
			//Close Shutter
			f << pointerToE545->setLimitsMacro(1, 0, 0, 0, 200);
		}

		f << "MOV A " << storPos[i][0] << " B " << storPos[i][1] << " C " << storPos[i][2] << endl;

		if (i == 0){
			f << "DEL " << (R / velocity) * 1000 * 2 << endl;
			f << pointerToE545->setLimitsMacro(1, 0, 200, 0, 0);
		}
		else{
			f << "DEL " << delay << endl;
		}

		if ((nOld != n)){
			//Open Shutter
			f << pointerToE545->setLimitsMacro(1, 0, 200, 0, 0);
		}

	}
	//Close Shutter
	f << pointerToE545->setLimitsMacro(1, 0, 0, 0, 200);
	//Geh zurück
	f << "DEL " << endl;
	f << "MAC END" << endl;
	f.close();

	cout << "Macro written to file:" << nameFile << endl;

	pointerToE545->sendMacros(nameFile);
	cout << "START MACRO" << endl;
	pointerToE545->closeShutter();
	pointerToE545->startMacro(macroName);
	pointerToE545->moveTo(pos);

}

//void figures::polygon::cutCircleViaMacro(){	
//	auto allPos = vector<vector<double>>(steps + 3, vector<double>(3));
//	Eigen::Vector3d pos;
//	pointerToE545->getPositon(pos);
//	cout << "pos:" << endl;
//	cout << pos << endl;
//
//	Eigen::Vector3d x1_Orts;
//	Eigen::Vector3d x2_Orts;
//	double l[3];
//	double y[3];
//
//	double deltaAlpha = (2 * pi) / steps;
//	double vec[3];
//	auto storPos = vector<vector<double>>(steps + 1, vector<double>(3));
//
//	double cX = 1;
//	double x1_1 = 30;
//	double x1_2 = 30;
//
//	double delay = 1000*(sin(deltaAlpha / 2) * 2 * R*delayFactor)/velocity;
//
//	string macroName = "macroCircle";
//	string nameFile = "macroCircle.txt";
//
//	fstream f;
//	f << fixed;
//	f << setprecision(5);
//	f.open(nameFile, fstream::out | fstream::trunc);
//	f.close();
//	f.open(nameFile, fstream::out | fstream::app);
//
////phi wird vernachlässigt
//
//	//Schneiden in x-y Ebenen xRotW = 0, zRotW wird vernachlässigt
//	if (rotAngleX == 0)
//	{
//
//		cout << "xy" << endl;
//
//		//////////////////////////////////////////
//		//		Generating the coordinates		//
//		//////////////////////////////////////////
//		for (int i = 0; i <= steps; i++){
//
//			vec[0] = R*cos(deltaAlpha*i);
//			vec[1] = R*sin(deltaAlpha*i);
//			vec[2] = 0;
//
//			storPos[i][0] = vec[0] + pos[0];
//			storPos[i][1] = vec[1] + pos[1];
//			storPos[i][2] = vec[2] + pos[2];
//		}
//
//		for (int i = 0; i < 3; i++){
//			y[i] = storPos[0][i] - pos[i];
//		}
//
//		l[0] = 0;
//		l[1] = x1_2;
//		l[2] = 0;
//
//		for (int i = 0; i < 3; i++){
//			x1_Orts[i] = storPos[0][i] + (y[i] / (use.norm(y))) * x1_1 - l[i];
//			x2_Orts[i] = storPos[0][i] + (y[i] / (use.norm(y))) * x1_1 + l[i];
//		}
//
//		//////////////////////////////////////////
//		//		Actual cutting procedure 		//
//		//////////////////////////////////////////
//
//		Eigen::Vector3d x1 = x1_Orts - pos;
//		double delayX = 1000*(x1.norm() / velocity)*cX;
//		
//
//		f << "MAC BEG " <<macroName << endl;
//		f << "VEL A " << velocity << " B " << velocity << " C " << velocity << endl;
//		//geh zu x1_Orts
//		f << "MOV A " << x1_Orts[0] << " B " << x1_Orts[1] << " C " << x1_Orts[2] << endl;
//		f << "DEL " << delayX << endl;
//		//setze limits
//		f << pointerToE545->setLimitsMacro(1, pos[0] - R, pos[0] + R,0,0);
//		for (int i = 0; i <= steps; i++){
//			f << "MOV A " << storPos[i][0] << " B " << storPos[i][1] << " C " << storPos[i][2] << endl;
//			f << "DEL " << delay << endl;
//		}
//		f << "VEL A " << 50 << " B " << 50 << " C " << 50 << endl;
//		f << "MOV A " << x2_Orts[0] << " B " << x2_Orts[1] << " C " << x2_Orts[2] << endl;
//		f << "DEL " << delayX << endl;
//		//Limits auf 0 0 0 setzen
//		f << pointerToE545->setLimitsMacro(1, 0, 0, pos[0] - R, pos[0] + R);
//		f << pointerToE545->setLimitsMacro(2, 0, 0, 0, 0);
//		f << pointerToE545->setLimitsMacro(3, 0, 0,0,0);
//		//Geh zurück
//		f << "MOV A " << pos[0] << " B " << pos[1] << " C " << pos[2] << endl;
//		f << "DEL " << delayX << endl;
//		f << "MAC END" << endl;
//
//	}
//
//	//Schneiden perpendicular zu xy-Ebene
//
//	if ((round((rotAngleX / (2 * pi)) * 360) == 270) || (round((rotAngleX / (2 * pi)) * 360) == 90))
//	{
//		cout << "pxy" << endl;
//		double xRotMat[3][3];
//		double zRotMat[3][3];
//		use.setRotMatrices(xRotMat, zRotMat, pi/2, rotAngleZ);
//
//		//////////////////////////////////////////
//		//		Generating the coordinates		//
//		//////////////////////////////////////////
//		for (int i = 0; i <= steps; i++){
//
//			vec[0] = R*cos(deltaAlpha*i+pi/2);
//			vec[1] = R*sin(deltaAlpha*i+pi/2);
//			vec[2] = 0;
//
//			use.matrixTimesVec(xRotMat, vec);
//			use.matrixTimesVec(zRotMat, vec);
//
//			storPos[i][0] = vec[0] + pos[0];
//			storPos[i][1] = vec[1] + pos[1];
//			storPos[i][2] = vec[2] + pos[2];
//		}
//
//		for (int i = 0; i < 3; i++){
//			y[i] = storPos[0][i] - pos[i];
//		}
//
//		l[0] = x1_2;
//		l[1] = 0;
//		l[2] = 0;
//
//		use.matrixTimesVec(zRotMat, l);
//
//		for (int i = 0; i < 3; i++){
//			x1_Orts[i] = storPos[0][i] + (y[i] / (use.norm(y))) * x1_1 + l[i];
//			x2_Orts[i] = storPos[0][i] + (y[i] / (use.norm(y))) * x1_1 - l[i];
//		}
//		
//
//		//////////////////////////////////////////
//		//		Actual cutting procedure 		//
//		//////////////////////////////////////////
//
//		Eigen::Vector3d x1 = x1_Orts - pos;
//		double delayX = 1000*ceil((x1.norm() / velocity)*cX);
//
//		f << "MAC BEG " << macroName << endl;
//		f << "VEL A " << velocity << " B " << velocity << " C " << velocity << endl;
//		//geh zu x1_Orts
//		f << "MOV A " << x1_Orts[0] << " B " << x1_Orts[1] << " C " << x1_Orts[2] << endl;
//		f << "DEL " << delayX << endl;
//		//setze limits
//		f << pointerToE545->setLimitsMacro(3, pos[2] - R, pos[2] + R,0,0);
//		for (int i = 0; i <= steps; i++){
//			f << "MOV A " << storPos[i][0] << " B " << storPos[i][1] << " C " << storPos[i][2] << endl;
//			f << "DEL " << delay << endl;
//		}
//		f << "MOV A " << x2_Orts[0] << " B " << x2_Orts[1] << " C " << x2_Orts[2] << endl;
//		f << "DEL " << delayX << endl;
//		//Limits auf 0 0 0 setzen
//		f << pointerToE545->setLimitsMacro(1, 0, 0,0,0);
//		f << pointerToE545->setLimitsMacro(2, 0, 0,0,0);
//		f << pointerToE545->setLimitsMacro(3, 0, 0, pos[2] - R, pos[2] + R);
//		//Geh zurück
//		f << "MOV A " << pos[0] << " B " << pos[1] << " C " << pos[2] << endl;
//		f << "DEL " << delayX << endl;
//		f << "MAC END" << endl;
//		
//	}
//
//	f.close();
//	pointerToE545->sendMacros(nameFile);
//
//	cout << "START MACRO" << endl;
//	getchar();
//	pointerToE545->closeShutter();
//	pointerToE545->startMacro(macroName);
//
//	//Write sequence to file for controle			
//	//###################################################################
//	for (int i = 0; i < steps + 3; i++){
//		for (int j = 0; j < 3; j++){
//
//
//			if (i == 0){
//
//				allPos[0][j] = x1_Orts[j];
//				
//			}
//
//			if (i == steps + 2){
//
//				allPos[steps + 2][j] = x2_Orts[j];
//
//			}
//
//			if ((i != steps + 2) && (i != 0)){
//				allPos[i][j] = storPos[i - 1][j];
//			}
//
//		}
//
//		
//	}
//	use.writeCoordToFile("circleCoordViamacro.txt", allPos, steps + 3);
//
//	//#####################################################################
//
//	if ((rotAngleX != 0) && !((round((rotAngleX / (2 * pi)) * 360) == 270) || (round((rotAngleX / (2 * pi)) * 360) == 90))){
//		cout << "For using circleMacroCut rotAngleX has to be equal to 0 or 90" << endl;
//		cout << "-> No cut done" << endl;
//	}
//}
