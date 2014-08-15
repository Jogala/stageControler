#include "figures.h"

//line 
void figures::line::loadValuesFromTextFile(){

	cout << "Load stored values for Line" << endl;
	fstream f;
	f.open(nameFile);

	string varName;
	string readOut="-1";
	if (f.is_open()) {

		//l
		varName = "l";
		while ((varName!=readOut)&&(!f.eof())) {

			f >> readOut;
		}

		if (varName == readOut){
			f >> l;
		}
		else{
			cout << "there was no new value found for l in"<< nameFile<< endl;
		}
		/////////////////////////////////////////////


		//phi
		varName = "phi";
		while ((varName != readOut) && (!f.eof())) {

			f >> readOut;
		}
		if (varName == readOut){
			f >> phi;
		}
		else{
			cout << "there was no new value found for phi in" << nameFile << endl;
		}
		/////////////////////////////////////////////


		//theta
		varName = "theta";
		while ((varName != readOut) && (!f.eof())) {

			f >> readOut;
		}
		if (varName == readOut){
			f >> theta;
		}
		else{
			cout << "there was no new value found for theta in" << nameFile << endl;
		}
		/////////////////////////////////////////////


		//repetitions
		varName = "repetitions";
		while ((varName != readOut) && (!f.eof())) {

			f >> readOut;
		}
		if (varName == readOut){
			f >> repetitions;
		}
		else{
			cout << "there was no new value found for repetitions in" << nameFile << endl;
		}
		/////////////////////////////////////////////


		//velocity
		varName = "velocity";
		while ((varName != readOut) && (!f.eof())) {

			f >> readOut;
		}
		if (varName == readOut){
			f >> velocity;
		}
		else{
			cout << "there was no new value found for velocity in" << nameFile << endl;
		}
		/////////////////////////////////////////////
	}
	f.close();

}
void figures::line::writeVariablesToTextFile(double lIn, double phiIn, double thetaIn, int repetitionsIn, double velocityIn){


	fstream f;
	f << fixed;
	f << setprecision(3);
	f.open(nameFile, fstream::out | fstream::trunc);
	f.close();
	f.open(nameFile, fstream::out | fstream::app);

	f << "l" <<"\t"<< lIn << endl;
	f << "phi" <<"\t"<< phiIn <<endl;
	f << "theta" << "\t" << thetaIn << endl;
	f << "repetitions" << "\t" <<repetitionsIn << endl;
	f << "velocity" << "\t"<< velocityIn<< endl;
	f.close();
	

}

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
			pointerToE545->move(x, y, 0);
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

void figures::line::set3D(double lIn, double phi0In, double thetaIn, double velocityIn, int repetionsIn){

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
			pointerToE545->move(-vec[0], -vec[1], -vec[2]);
			repetitions = repetitions - 1;
		}
		pointerToE545->closeShutter();
		pointerToE545->moveTo(pos);
	}
}
void figures::line::cutAbs3D(){

	if (repetitions < 1){

		cout << endl;
		cout << "ERROR:" << endl;
		cout << "repetitions has to be >= 1" << endl;

	}
	else{

		pointerToE545->setVelocity(velocity, velocity, velocity);

		double vec[3];
		double pos[3];
		auto storagePos = vector<vector<double>>(repetitions, vector<double>(3));

		pointerToE545->getPositon(pos);

		vec[0] = l*cos(phi)*sin(theta);
		vec[1] = l*sin(phi)*sin(theta);
		vec[2] = l*cos(theta);

		//////////////////////////////////////////////////////////////////////////
		//		Generating the sequence of coordinates that will be visited		//
		//////////////////////////////////////////////////////////////////////////


		for (int i = 0; i < repetitions; i++)
		{
			if (i % 2 == 0){
				storagePos[i][0] = pos[0] + vec[0];
				storagePos[i][1] = pos[1] + vec[1];
				storagePos[i][2] = pos[2] + vec[2];
			}

			if (i % 2 == 1){
				storagePos[i][0] = pos[0];
				storagePos[i][1] = pos[1];
				storagePos[i][2] = pos[2];
			}
		}
		//////////////////////////////////////////////////////
		//		Write sequence to file for controle			//
		//////////////////////////////////////////////////////

		use.writeCoordToFile("line3DAbs.txt", storagePos, repetitions);


		//////////////////////////////////////////
		//		Actual cutting procedure 		//
		//////////////////////////////////////////

		pointerToE545->openShutter();
		for (int i = 0; i < repetitions; i++){

			pointerToE545->moveTo(storagePos[i][0], storagePos[i][1], storagePos[i][2]);

		}
		pointerToE545->closeShutter();
		pointerToE545->setVelocity(1000, 1000, 1000);
		pointerToE545->moveTo(pos[0], pos[1], pos[2]);

	}//else

}
void figures::line::cutAbsLim3D(){

	if (repetitions < 1){

		cout << endl;
		cout << "ERROR:" << endl;
		cout << "repetitions has to be >= 1" << endl;

	}
	else{

		pointerToE545->setVelocity(velocity, velocity, velocity);

		double vec[3];
		double pos[3];
		auto storagePos = vector<vector<double>>(repetitions, vector<double>(3));

		pointerToE545->getPositon(pos);

		vec[0] = l*cos(phi)*sin(theta);
		vec[1] = l*sin(phi)*sin(theta);
		vec[2] = l*cos(theta);

		int limAxis = use.axisOfBiggestProjection(vec);
		double c = 10;
		double normOfVec = use.norm(vec);

		//////////////////////////////////////////////////////////////////////////
		//		Generating the sequence of coordinates that will be visited		//
		//////////////////////////////////////////////////////////////////////////

		for (int i = 0; i < repetitions; i++)
		{
			if (i % 2 == 1){
				storagePos[i][0] = pos[0] + vec[0] + c*vec[0] / normOfVec;
				storagePos[i][1] = pos[1] + vec[1] + c*vec[1] / normOfVec;
				storagePos[i][2] = pos[2] + vec[2] + c*vec[2] / normOfVec;
			}

			if (i % 2 == 0){
				storagePos[i][0] = pos[0] - c*vec[0] / normOfVec;
				storagePos[i][1] = pos[1] - c*vec[1] / normOfVec;
				storagePos[i][2] = pos[2] - c*vec[2] / normOfVec;
			}
		}

		//////////////////////////////////////////////////////
		//		Write sequence to file for controle			//
		//////////////////////////////////////////////////////

		use.writeCoordToFile("line3DAbs.txt", storagePos, repetitions);

		//////////////////////////////////////////
		//		Actual cutting procedure 		//
		//////////////////////////////////////////

		//A
		pointerToE545->moveTo(storagePos[0][0], storagePos[0][1], storagePos[0][2]);
		pointerToE545->setLimits(limAxis, pos[limAxis], pos[limAxis] + vec[limAxis]);

		for (int i = 1; i <= repetitions; i++){

			pointerToE545->moveTo(storagePos[i][0], storagePos[i][1], storagePos[i][2]);

		}
		pointerToE545->closeShutter();
		pointerToE545->setVelocity(1000, 1000, 1000);
		pointerToE545->moveTo(pos[0], pos[1], pos[2]);

	}//else

}

bool figures::line::regMenuWindow(){

	HINSTANCE hInstance = GetModuleHandle(0);
	WNDCLASSEX wcLine;

	wcLine.cbSize = sizeof(WNDCLASSEX);
	wcLine.style = 0;
	wcLine.lpfnWndProc = WndProcNewLine3D;
	wcLine.cbClsExtra = 0;
	wcLine.cbWndExtra = 0;
	wcLine.hInstance = hInstance;
	wcLine.hIcon = NULL;
	wcLine.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wcLine.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcLine.lpszMenuName = NULL;
	wcLine.lpszClassName = "line";
	wcLine.hIconSm = NULL;

	// This function actually registers the window class. If the information specified in the 'wcLine' struct is correct,
	// the window class should be created and no error is returned.
	if (!RegisterClassEx(&wcLine))
	{
		cout << "RegisterClassEx failed" << endl;
		return 0;
	}

}
void figures::line::openWindowSet3D(){

	HWND hwnd;
	HWND h_text_l;

	HINSTANCE hInstance = GetModuleHandle(0);


	hwnd = CreateWindowExA(WS_EX_CLIENTEDGE, "line", "",
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

	double phiInDeg = round((phi / (2 * pi))*(360));
	double thetaInDeg = round((theta / (2 * pi))*(360));

	string sL = use.numberToString(l);
	string sPhi = use.numberToString(phiInDeg);
	string sTheta = use.numberToString(thetaInDeg);
	string sRepetitions = use.numberToString(repetitions);
	string sVelocity = use.numberToString(velocity);

	//Headline
	CreateWindow("STATIC", "Line 3D ", WS_VISIBLE | WS_CHILD | SS_CENTER, xS, top, 290, hEaS,
		hwnd, NULL, hInstance, NULL);
	top += deltaY;

	CreateWindow("STATIC", "currently", WS_VISIBLE | WS_CHILD | SS_RIGHT, xSC, top, bSC, hEaS,
		hwnd, NULL, hInstance, NULL);
	top += deltaY;

	//l
	CreateWindow("STATIC", "l = ", WS_VISIBLE | WS_CHILD | SS_RIGHT, xS, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);

	h_text_l = CreateWindow("EDIT", sL.c_str(), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, xE, top, bE, hEaS,
		hwnd, (HMENU)ID_TEXT_LINE_l, hInstance, NULL);

	CreateWindow("STATIC", sL.c_str(), WS_VISIBLE | WS_CHILD | SS_RIGHT, xSC, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);


	top += deltaY;

	//phi
	CreateWindow("STATIC", "phi = ", WS_VISIBLE | WS_CHILD | SS_RIGHT, xS, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	CreateWindow("EDIT", sPhi.c_str(), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, xE, top, bE, hEaS,
		hwnd, (HMENU)ID_TEXT_LINE_phi, hInstance, NULL);
	CreateWindow("STATIC", sPhi.c_str(), WS_VISIBLE | WS_CHILD | SS_RIGHT, xSC, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);

	top += deltaY;

	//theta
	CreateWindow("STATIC", "theta = ", WS_VISIBLE | WS_CHILD | SS_RIGHT, xS, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	CreateWindow("EDIT", sTheta.c_str(), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, xE, top, bE, hEaS,
		hwnd, (HMENU)ID_TEXT_LINE_theta, hInstance, NULL);
	CreateWindow("STATIC", sTheta.c_str(), WS_VISIBLE | WS_CHILD | SS_RIGHT, xSC, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	top += deltaY;

	//repetitions
	CreateWindow("STATIC", "repetitions = ", WS_VISIBLE | WS_CHILD | SS_RIGHT, xS, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	CreateWindow("EDIT", sRepetitions.c_str(), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, xE, top, bE, hEaS,
		hwnd, (HMENU)ID_TEXT_LINE_repetitions, hInstance, NULL);
	CreateWindow("STATIC", sRepetitions.c_str(), WS_VISIBLE | WS_CHILD | SS_RIGHT, xSC, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	top += deltaY;

	//velocity
	CreateWindow("STATIC", "velocity = ", WS_VISIBLE | WS_CHILD | SS_RIGHT, xS, top, bS, hEaS,
		hwnd, NULL, hInstance, NULL);
	CreateWindow("EDIT", sVelocity.c_str(), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, xE, top, bE, hEaS,
		hwnd, (HMENU)ID_TEXT_LINE_velocity, hInstance, NULL);
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
		(HMENU)ID_OK_KNOPF_LINE,                        /* control''s ID for WM_COMMAND */
		hInstance,                                /* application instance */
		NULL);


	//Show the window including all controls.
	ShowWindow(hwnd, 5);
	UpdateWindow(hwnd);
	SetForegroundWindow(hwnd);

	//set h_text_l on focus and mark text, such that user can start typing new values immidiately
	//////////////////////////////////////////////////////////////////////////////////////////////
	SetFocus(h_text_l);
	SendDlgItemMessage(hwnd, ID_TEXT_LINE_l, EM_SETSEL, 0, -1);
	//////////////////////////////////////////////////////////////////////////////////////////////

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



		if (line_BOOL)
		{

			double tempL, tempPhi, tempTheta, tempVelocity;
			int tempRep;

			use.constCharToNumber(G_Text_line_l, tempL);

			use.constCharToNumber(G_Text_line_phi,tempPhi);
			tempPhi = round(tempPhi);
			tempPhi = (tempPhi / 360) * 2 * pi;

			use.constCharToNumber(G_Text_line_theta, tempTheta);
			cout << "tempTheta = " << tempTheta << endl;
			tempTheta = round(tempTheta);
			cout << "tempTheta = " << tempTheta << endl;
			tempTheta = (tempTheta / 360) * 2 * pi;

			use.constCharToNumber(G_Text_line_repetitions, tempRep);
			use.constCharToNumber(G_Text_line_velocity, tempVelocity);			

			writeVariablesToTextFile(tempL, tempPhi, tempTheta, tempRep, tempVelocity);
			loadValuesFromTextFile();
			printMemberValues();

			line_BOOL = 0;
		}
	}//while 

}



