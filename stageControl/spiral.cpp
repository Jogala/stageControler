#include "figures.h"

void figures::spiral::cutAbsMacroSpiral3D(){

	double R = itsR;
	int sectors = 4;
	double deltaR = (R*radiusRatio) / sectors;
	cout << "deltaR = " << deltaR << endl;
	int stepsPerSector = steps / sectors;
	cout << "stepsPerSector = " << stepsPerSector << endl;
	double pos[3];

	//pointerToE545->getPositon(pos);
	pos[0] = 0;
	pos[1] = 0;
	pos[2] = 0;

	double deltaAlpha = (2 * pi) / steps;
	double vec[3];
	auto storPos = vector<vector<double>>(steps + 1, vector<double>(3));
	auto delay = vector<double>(steps + 1);
	
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
	int nOld = n;
	for (int i = 1; i <= steps + 1; i++){

		if ((i - 1) == 0){

			delay[0] = (R / velocity) * 1000;
		
		}
		else{

			if (nOld != n){

				R = R - deltaR;
				delay[(i - 1)] = (deltaR / velocity) * 1000;

			}
			else{

				delay[(i - 1)] = 1000 * (sin(deltaAlpha / 2) * 2 * R*delayFactor) / velocity;

			}
		}

		vec[0] = R*cos(deltaAlpha*(i - 1) + pi / 2);
		vec[1] = R*sin(deltaAlpha*(i - 1) + pi / 2);
		vec[2] = 0;

		use.matrixTimesVec(xRotMat, vec);
		use.matrixTimesVec(zRotMat, vec);

		storPos[(i - 1)][0] = vec[0] + pos[0];
		storPos[(i - 1)][1] = vec[1] + pos[1];
		storPos[(i - 1)][2] = vec[2] + pos[2];

		nOld = n;
		n = i / stepsPerSector;
	
		if (n == sectors){
			n = n - 1;
		}

		
		
	}

	int color = 1;
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
		
		for (int j = 0; j < 3; j++){

			fc << storPos[i][j] << "\t";
		}

		fc << delay[i] << endl;
	
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
	f << "MOV A " << storPos[0][0] << " B " << storPos[0][1] << " C " << storPos[0][2] << endl;
	f << "DEL " << delay[0] << endl;
	f << pointerToE545->setLimitsMacro(1, 0, 200, 0, 0);
	
	int shutterCounter=0; 
	for (int i = 1; i < steps + 1; i++){

		if (i>=2){
			if (delay[i] != delay[i - 1]){

				if (!(shutterCounter % 2)){
					//Close Shutter
					f << pointerToE545->setLimitsMacro(1, 0, 0, 0, 200);
				}
				else{
					//Open Shutter
					f << pointerToE545->setLimitsMacro(1, 0, 200, 0, 0);
				}
				shutterCounter = shutterCounter + 1;
			}
		}

			f << "MOV A " << storPos[i][0] << " B " << storPos[i][1] << " C " << storPos[i][2] << endl;
			f << "DEL " << delay[i] << endl;

	}
	//Close Shutter
	f << pointerToE545->setLimitsMacro(1, 0, 0, 0, 200);
	f << "DEL " << endl;
	f << "MAC END" << endl;
	f.close();

	cout << "Macro written to file:" << nameFile << endl;
	cout << "SENDING MACRO TO CONTROLLER..." << endl;
	pointerToE545->sendMacros(nameFile);

	pointerToE545->closeShutter();
	pointerToE545->startMacroAndWaitWhileRunning(macroName);
	pointerToE545->closeShutter();
	pointerToE545->moveTo(pos);

}

bool figures::spiral::regMenuWindow(){

	HINSTANCE hInstance = GetModuleHandle(0);
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProcNewSpiral;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "spiral";
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
void figures::spiral::openWindowSet3D(){

	HWND hwnd;
	HWND h_text_R;

	HINSTANCE hInstance = GetModuleHandle(0);

	hwnd = CreateWindowExA(WS_EX_CLIENTEDGE, "spiral", "",
		(WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX),
		CW_USEDEFAULT, CW_USEDEFAULT, 330, 410, NULL, NULL, hInstance, NULL);

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

	double rotAngleXInDeg = round((rotAngleX / (2 * pi))*(360));
	double rotAngleZInDeg = round((rotAngleZ / (2 * pi))*(360));
	double phi0InDeg = round((phi0 / (2 * pi))*(360));

	const string sR = use.numberToString(itsR);
	const string sPhi0 = use.numberToString(phi0InDeg);
	const string sSteps = use.numberToString(steps);
	const string sRotAngleX = use.numberToString(rotAngleXInDeg);
	const string sRotAngleZ = use.numberToString(rotAngleZInDeg);
	const string sVelocity = use.numberToString(velocity);
	const string sSectors = use.numberToString(sectors);
	const string sRadiusRatio = use.numberToString(radiusRatio);

	//Headline
	CreateWindow("STATIC", "SPIRAL 3D ", WS_VISIBLE | WS_CHILD | SS_CENTER, xS, top, 290, hEaS,
		hwnd, NULL, hInstance, NULL);
	top += deltaY;

	CreateWindow("STATIC", "currently", WS_VISIBLE | WS_CHILD | SS_RIGHT, xSC, top, bSC, hEaS,
		hwnd, NULL, hInstance, NULL);
	top += deltaY;

	//R
	CreateWindow("STATIC", "R = ", WS_VISIBLE | WS_CHILD | SS_RIGHT, xS, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);

	h_text_R = CreateWindow("EDIT", sR.c_str(), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, xE, top, bE, hEaS,
		hwnd, (HMENU)ID_TEXT_SPIRAL_R, hInstance, NULL);

	CreateWindow("STATIC", sR.c_str(), WS_VISIBLE | WS_CHILD | SS_RIGHT, xSC, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);


	top += deltaY;

	//phi0
	CreateWindow("STATIC", "phi0 = ", WS_VISIBLE | WS_CHILD | SS_RIGHT, xS, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	CreateWindow("EDIT", sPhi0.c_str(), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, xE, top, bE, hEaS,
		hwnd, (HMENU)ID_TEXT_SPIRAL_phi0, hInstance, NULL);
	CreateWindow("STATIC", sPhi0.c_str(), WS_VISIBLE | WS_CHILD | SS_RIGHT, xSC, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);

	top += deltaY;

	//xRotAngle
	CreateWindow("STATIC", "xRotAngle = ", WS_VISIBLE | WS_CHILD | SS_RIGHT, xS, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	CreateWindow("EDIT", sRotAngleX.c_str(), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, xE, top, bE, hEaS,
		hwnd, (HMENU)ID_TEXT_SPIRAL_xRotWinkel, hInstance, NULL);
	CreateWindow("STATIC", sRotAngleX.c_str(), WS_VISIBLE | WS_CHILD | SS_RIGHT, xSC, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	top += deltaY;

	//zRotAngle
	CreateWindow("STATIC", "zRotAngle = ", WS_VISIBLE | WS_CHILD | SS_RIGHT, xS, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	CreateWindow("EDIT", sRotAngleZ.c_str(), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, xE, top, bE, hEaS,
		hwnd, (HMENU)ID_TEXT_SPIRAL_zRotWinkel, hInstance, NULL);
	CreateWindow("STATIC", sRotAngleZ.c_str(), WS_VISIBLE | WS_CHILD | SS_RIGHT, xSC, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	top += deltaY;

	//steps
	CreateWindow("STATIC", "steps = ", WS_VISIBLE | WS_CHILD | SS_RIGHT, xS, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	CreateWindow("EDIT", sSteps.c_str(), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, xE, top, bE, hEaS,
		hwnd, (HMENU)ID_TEXT_SPIRAL_steps, hInstance, NULL);
	CreateWindow("STATIC", sSteps.c_str(), WS_VISIBLE | WS_CHILD | SS_RIGHT, xSC, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	top += deltaY;

	//sectors
	CreateWindow("STATIC", "sectors = ", WS_VISIBLE | WS_CHILD | SS_RIGHT, xS, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	CreateWindow("EDIT", sSectors.c_str(), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, xE, top, bE, hEaS,
		hwnd, (HMENU)ID_TEXT_SPIRAL_sectors, hInstance, NULL);
	CreateWindow("STATIC", sSectors.c_str(), WS_VISIBLE | WS_CHILD | SS_RIGHT, xSC, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	top += deltaY;

	//radiusRatio
	CreateWindow("STATIC", "radiusRatio = ", WS_VISIBLE | WS_CHILD | SS_RIGHT, xS, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	CreateWindow("EDIT", sRadiusRatio.c_str(), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, xE, top, bE, hEaS,
		hwnd, (HMENU)ID_TEXT_SPIRAL_radiusRatio, hInstance, NULL);
	CreateWindow("STATIC", sRadiusRatio.c_str(), WS_VISIBLE | WS_CHILD | SS_RIGHT, xSC, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	top += deltaY;

	//velocity
	CreateWindow("STATIC", "velocity = ", WS_VISIBLE | WS_CHILD | SS_RIGHT, xS, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	CreateWindow("EDIT", sVelocity.c_str(), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, xE, top, bE, hEaS,
		hwnd, (HMENU)ID_TEXT_SPIRAL_velocity, hInstance, NULL);
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
		(HMENU)ID_OK_KNOPF_SPIRAL,                        /* control''s ID for WM_COMMAND */
		hInstance,                                /* application instance */
		NULL);


	//Show the window including all controls.
	ShowWindow(hwnd, 5);
	UpdateWindow(hwnd);
	SetForegroundWindow(hwnd);

	//set h_text_R on focus and mark text, such that user can start typing new values immidiately
	SetFocus(h_text_R);
	SendDlgItemMessage(hwnd, ID_TEXT_SPIRAL_R, EM_SETSEL, 0, -1);


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
		
		if (spiral_BOOL)
		{
			//R
			use.assignValueToMember(G_Text_Spiral_R, itsR, "R");

			//phi0
			use.assignValueToMember(G_Text_Spiral_phi0, phi0, "phi0");
			phi0 = (phi0 / 360)*(2 * pi);
			//steps
			use.assignValueToMember(G_Text_Spiral_steps, steps, "steps");

			//rotangleX
			use.assignValueToMember(G_Text_Spiral_xRotWinkel, rotAngleX, "rotanglex");

			while (rotAngleX < 0){
				rotAngleX = rotAngleX + 360;
			}

			while (rotAngleX> 360){
				rotAngleX = rotAngleX - 360;
			}

			rotAngleX = (rotAngleX / 360)*(2 * pi);

			//rotAngleZ
			use.assignValueToMember(G_Text_Spiral_zRotWinkel, rotAngleZ, "rotAngleZ");

			while (rotAngleX < 0){
				rotAngleZ = rotAngleZ + 360;
			}

			while (rotAngleX> 360){
				rotAngleZ = rotAngleZ - 360;
			}

			rotAngleZ = (rotAngleZ / 360)*(2 * pi);

			//velocity
			use.assignValueToMember(G_Text_Spiral_velocity, velocity, "velocity");

			//sectors
			use.assignValueToMember(G_Text_Spiral_sectors, sectors, "sectors");

			//sectors
			use.assignValueToMember(G_Text_Spiral_radiusRatio, radiusRatio, "radiusRatio");

			//Export Values s.t. they can be loaded the next time the program starts
			string name = "spiralLastValues.txt";
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
			f << sectors << endl;
			f << radiusRatio << endl;
			f << velocity << endl;
			f.close();

			spiral_BOOL = 0;
		}
	}//while 





}
void figures::spiral::loadValuesFromTextFile(){

	cout << "Old Values Spiral" << endl;
	fstream myReadFile;
	myReadFile.open("spiralLastValues.txt");

	int i = 0;
	if (myReadFile.is_open()) {
		while (i < 7) {

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
				myReadFile >> sectors;
				cout << sectors << endl;
				i++;
			}
			if (i == 6){
				myReadFile >> radiusRatio;
				cout << radiusRatio << endl;
				i++;
			}
			if (i == 7){
				myReadFile >> velocity;
				cout << velocity << endl;
				i++;
			}
		}
	}
	myReadFile.close();

}