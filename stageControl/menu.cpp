#include "menu.h"
 
void menu::helpMenu(){
	
	string STRING;
	ifstream infile;
	infile.open("./Resources/listOfCommands.txt");
	while (!infile.eof()) // To get you all the lines.
	{
		getline(infile, STRING); // Saves the line in STRING.
		cout << STRING << endl; // Prints our STRING.
	}
	infile.close();

}
void menu::settingsMenu(){

	//Just clearing the current command line
	const int KEYEVENT_KEYUP = 0x02;
	keybd_event(VK_ESCAPE, 0, 0, 0);              // press the Esc key
	keybd_event(VK_ESCAPE, 0, KEYEVENT_KEYUP, 0); // let up the Esc key

	string choice;
	cout << endl;
	cout << "Set..." << endl;
	cout << "--------------------------------------------" << endl;
	cout << " stepSize for axis: (x), (y), (z) or (a)ll " << endl;
	cout << "  velocityStepSize: (vx), (vy), (vz) or (v)" << endl;
	cout << "-------------------------------------------------------------" << endl;
	cout << "    pulsed shutter: - (s)hutter(O)pen(T)ime\t\t(sot)" << endl;
	cout << "                    - min(S)hutter(C)losed(T)ime\t(sct)" << endl;
	cout << "                    - set both \t\t\t\t(st)" << endl;
	cout << "-------------------------------------------------------------" << endl;
	cout << "-------------------------------------------------------------" << endl;
	cout << endl;
	cout << "MACROS" << endl;
	cout << "-------------------------------------------------------------" << endl;
	cout << "(d)elayFactor" << endl;
	cout << "-------------------------------------------------------------" << endl;
	cout << endl;
	cout << "-------------------------------------------------------------" << endl;
	cout << "Bring cut into focus:" << endl;
	cout << "-------------------------------------------------------------" << endl;
	cout << "(f)ocus" << endl;
	cin >> choice;

	if (choice == "f"){
		double deltaX, deltaY, deltaZ;
		cout << "deltaX = ";
		useful.cinAndCheckForDouble(deltaX);
		cout << "deltaY = ";
		useful.cinAndCheckForDouble(deltaY);
		cout << "deltaZ = ";
		useful.cinAndCheckForDouble(deltaZ);
		pToE545->setFocus_and_writeValuesToFile(deltaX, deltaY, deltaZ);
	}

	if (choice == "d"){
		double delayFactor;
		cout << "delayFactor = ";
		cin >> delayFactor;
		polygon.delayFactor = delayFactor;
		spiral.delayFactor = delayFactor;
		rectangle.delayFactor = delayFactor;
		line.delayFactor = delayFactor;
	}

	//axis Step Size 
	if (choice == "a"){
		cout << "xStepSize = ";
		useful.cinAndCheckForDoubleAndLimits(stepSize[0]);
		cout << "yStepSize = ";
		useful.cinAndCheckForDoubleAndLimits(stepSize[1]);
		cout << "zStepSize = ";
		useful.cinAndCheckForDoubleAndLimits(stepSize[2]);
	}
	if (choice == "x"){
		cout << "xStepSize = ";
		useful.cinAndCheckForDoubleAndLimits(stepSize[0]);
	}
	if (choice == "y"){
		cout << "yStepSize = ";
		useful.cinAndCheckForDoubleAndLimits(stepSize[1]);
	}
	if (choice == "z"){
		cout << "zStepSize = ";
		useful.cinAndCheckForDoubleAndLimits(stepSize[2]);
	}


	//Velocity Step Size
	if (choice == "vx"){
		cout << "xVelocityStepSize = ";
		useful.cinAndCheckForDoubleAndLimits(velStepSize[0]);
	}

	if (choice == "vy"){
		cout << "yVelocityStepSize = ";
		useful.cinAndCheckForDoubleAndLimits(velStepSize[1]);
	}
	if (choice == "vz"){
		cout << "zVelocityStepSize = ";
		useful.cinAndCheckForDoubleAndLimits(velStepSize[2]);
	}

	// pulsed shutter
	if (choice == "sot"){
		cout << "sot = ";
		useful.cinAndCheckForDoubleAndLimits(shutterOpenTime, 0);
	}
	if (choice == "sct"){
		cout << "sct = ";
		useful.cinAndCheckForDoubleAndLimits(minShutterClosedTime, 0);
	}
	if (choice == "st"){
		cout << "sot = ";
		useful.cinAndCheckForDoubleAndLimits(shutterOpenTime, 0);
		cout << "sct = ";
		useful.cinAndCheckForDoubleAndLimits(minShutterClosedTime, 0);
	}



}
void menu::printMenu(){

	//p print current position or velocity or limits
	//Just clearing the current command line
	const int KEYEVENT_KEYUP = 0x02;
	keybd_event(VK_ESCAPE, 0, 0, 0);              // press the Esc key
	keybd_event(VK_ESCAPE, 0, KEYEVENT_KEYUP, 0); // let up the Esc key

	string choice;
	cout << "print current (p)position, (v)velocities, (l)imits, (puls)Duration, \n (s)piral parameter,  (m)acro parameters, (E545) paramter" << endl;
	cin >> choice;

	if (choice == "p")
	{
		pToE545->printPosition();
	}
	if (choice == "v")
	{
		pToE545->printVelocity();
	}
	if (choice == "l")
	{
		pToE545->printLimits();
	}
	if (choice == "puls")
	{
		cout << "shutterOpenTime = " << shutterOpenTime << endl;
		cout << "minshutterClosedTime = " << minShutterClosedTime << endl;
	}
	if (choice == "s")
	{
		spiral.printMemberVariables();
	}

	if (choice == "m")
	{
		cout << "spiral.delayFactor = \t" << spiral.delayFactor << endl;
		cout << "rectangle.delayFactor = " << rectangle.delayFactor << endl;
		cout << "line.delayFactor = \t" << line.delayFactor << endl;
		cout << "polygon.delayFactor = \t" << polygon.delayFactor << endl;
	}

	if (choice == "E545")
	{
		pToE545->printMemberVariables();
	}
	

}
void menu::cutMainMenu(){

	//Just clearing the current command line
	const int KEYEVENT_KEYUP = 0x02;
	keybd_event(VK_ESCAPE, 0, 0, 0);              // press the Esc key
	keybd_event(VK_ESCAPE, 0, KEYEVENT_KEYUP, 0); // let up the Esc key

	string choice;
	cout << "n for set up (n)ew figure and (c) for (c)ut:" << endl;
	cin >> choice;


	if (choice == "n"){

		cutNewFigureMenu();
	}

	if (choice == "c"){

		cutCutMenu();
	}


}
void menu::cutNewFigureMenu(){

	string  choice;
	cout << "----cutNewFigureMenu----" << endl;
	cout << "(l)ine" << endl;
	cout << "(r)ectangle" << endl;
	cout << "(p)olygon" << endl;
	cout << "(s)piral" << endl;

	cin >> choice;

	if (choice == "r"){
		rectangle.openWindowSet3D();
	}

	if (choice == "p"){
		polygon.openWindowSet3D();
	}

	if (choice == "l"){
		line.openWindowSet3D();
	}

	if (choice == "s"){
		spiral.openWindowSet3D();
	}
}
void menu::cutCutMenu(){
	string choice;
	
	cout << "Choose figure to cut:" << endl;
	cout << "------------line------------" << endl;
	cout << "(l) \t\t 3D" << endl;
	cout << "------------rectangle------------" << endl;
	cout << "(r) \t\t 3D" << endl;
	cout << "------------polygon------------" << endl;
	cout << "(p)olygon \t\t 3D" << endl;
	cout << "------------spiral------------" << endl;
	cout << "(s)piral \t\t 3D" << endl;

	cin >> choice;
	bool focus = 0;

	//line
	if (choice == "l"){
		line.cutAbs3D();
		focus = 1;
	}
	
	//rectangle
	if (choice == "r"){
		rectangle.cutAbs3D();
		focus = 1;
	}

	//polygon
	if (choice == "p"){
		polygon.cutAbsMacro3D();
		focus = 1;

		pToE545->closeConnection();
		pToE545->establishConnection();
	}

	//spiral
	if (choice == "s"){
		spiral.cutAbsMacroSpiral3D();
		focus = 1;

		pToE545->closeConnection();
		pToE545->establishConnection();
	}

	if (focus){
		cout << "press ENTER for getting back to 100, 100 ,100" << endl;
		
		// if enter is already pressed, wait for
		// it to be released
		while (GetAsyncKeyState(VK_RETURN) & 0x8000) {
			Sleep(100);
		}

		// wait for enter to be pressed
		while (!(GetAsyncKeyState(VK_RETURN) & 0x8000)) {
			Sleep(100);
		}
		
		pToE545->moveTo(100, 100, 100);
	}
}
void menu::moveToMenu(){

		double target[3];
		cout << "moveTo" << endl;
		cout << "xTarget = ";
		useful.cinAndCheckForDouble(target[0]);
		cout << "yTarget = ";
		useful.cinAndCheckForDouble(target[1]);
		cout << "zTarget = ";
		useful.cinAndCheckForDouble(target[2]);

		pToE545->moveTo(target);
		pToE545->printPosition();

}
void menu::moveUsingArrowsMenu(const bool windowActive){
	//left
	while ((GetKeyState(0x25) & 0x8000) && windowActive)
	{
		pToE545->move(-1.0*stepSize[0], 0, 0);
		pToE545->printPosition();
		Sleep(sleepValue);
	}//left

	//right
	while ((GetKeyState(0x27) & 0x8000) && windowActive)
	{
		pToE545->move(1.0*stepSize[0], 0, 0);
		pToE545->printPosition();
		Sleep(sleepValue);
	}//right

	//down
	while ((GetKeyState(0x28) & 0x8000) && windowActive)
	{
		pToE545->move(0, -1.0*stepSize[1], 0);
		pToE545->printPosition();
		Sleep(sleepValue);
	}//down

	//up
	while ((GetKeyState(0x26) & 0x8000) && windowActive)
	{
		pToE545->move(0, 1.0*stepSize[1], 0);
		pToE545->printPosition();
		Sleep(sleepValue);
	}//up

	//page - up
	while ((GetKeyState(0x21) & 0x8000) && windowActive)
	{
		pToE545->move(0, 0, stepSize[2]);
		pToE545->printPosition();
		Sleep(sleepValue);
	}//page - up

	//page - down
	while ((GetKeyState(0x22) & 0x8000) && windowActive)
	{
		pToE545->move(0, 0, -1.0*stepSize[2]);
		pToE545->printPosition();
		Sleep(sleepValue);
	}//page - down
}
void menu::controlVelocitiesMenu(const bool windowActive){

	//x-Achse Velocity +  == 4
	while ((GetKeyState(0x64) & 0x8000) && windowActive)
	{
		pToE545->deltaVelocity(velStepSize[0], 0, 0);
		pToE545->printVelocity();
		Sleep(sleepValue);
	}//4

	//x-Achse Velocity - == 1
	while ((GetKeyState(0x61) & 0x8000) && windowActive)
	{
		pToE545->deltaVelocity(-1.0*velStepSize[0], 0, 0);
		pToE545->printVelocity();
		Sleep(sleepValue);
	}//1

	//y-Achse Velocity +  == 5
	while ((GetKeyState(0x65) & 0x8000) && windowActive)
	{
		pToE545->deltaVelocity(0, velStepSize[1], 0);
		pToE545->printVelocity();
		Sleep(sleepValue);

	}//5

	//y-Achse Velocity - ==2
	while ((GetKeyState(0x62) & 0x8000) && windowActive)
	{
		pToE545->deltaVelocity(0, -1.0*velStepSize[1], 0);
		pToE545->printVelocity();
		Sleep(sleepValue);
	}//2

	//y-Achse Velocity +  == 6
	while ((GetKeyState(0x66) & 0x8000) && windowActive)
	{
		pToE545->deltaVelocity(0, 0, velStepSize[2]);
		pToE545->printVelocity();
		Sleep(sleepValue);

	}//5

	//y-Achse Velocity - ==3
	while ((GetKeyState(0x63) & 0x8000) && windowActive)
	{
		pToE545->deltaVelocity(0, 0, -1.0*velStepSize[2]);
		pToE545->printVelocity();
		Sleep(sleepValue);
	}//2

}
void menu::openShutterMenu(){
	
	if (pToE545->checkIfAnyLimit()){
		pToE545->closeShutter();
	}
	else
	{
		pToE545->openShutter();
	}

	Sleep(5 * sleepValue);
}
void menu::openShutterPulsedMenu(){

	if (pToE545->checkIfAnyLimit()){
		pToE545->closeShutter();
		Sleep(shutterOpenTime);
		pToE545->openShutter();
	}
	else
	{
		pToE545->openShutter();
		Sleep(shutterOpenTime);
		pToE545->closeShutter();
	}

	Sleep(minShutterClosedTime);

}
void menu::setLimitsMenu(){

		//Just clearing the current command line
		const int KEYEVENT_KEYUP = 0x02;
		keybd_event(VK_ESCAPE, 0, 0, 0);              // press the Esc key
		keybd_event(VK_ESCAPE, 0, KEYEVENT_KEYUP, 0); // let up the Esc key

		string choice0;
		string choice1;
		string choice;
		double min;
		double max;

		pToE545->setTriggerMode(1, 3);
		pToE545->setTriggerMode(2, 3);
		pToE545->setTriggerMode(3, 3);

		cout << "set min max (s)eperately or set (l)limits" << endl;
		cin >> choice0;

		if (choice0 == "l"){

			cout << "set limits, press x, y or z" << endl;
			cin >> choice1;

			if (choice1 == "x"){
				cout << "min = ";
				useful.cinAndCheckForDouble(min);
				cout << "max = ";
				useful.cinAndCheckForDouble(max);
				pToE545->setLimits(1, min, max);
			}
			if (choice1 == "y"){
				cout << "min = ";
				useful.cinAndCheckForDouble(min);
				cout << "max = ";
				useful.cinAndCheckForDouble(max);
				pToE545->setLimits(2, min, max);
			}
			if (choice1 == "z"){
				cout << "min = ";
				useful.cinAndCheckForDouble(min);
				cout << "max = ";
				useful.cinAndCheckForDouble(max);
				pToE545->setLimits(3, min, max);
			}
		}

		if (choice0 == "s"){

			cout << "set min or max, type xMax, xMin, yMin or yMax" << endl;
			cin >> choice1;

			if (choice1 == "xMax"){
				cout << "xMax = ";
				cin >> max;
				pToE545->setLimitsMax(1, max);
			}
			if (choice1 == "xMin"){
				cout << "xMin = ";
				cin >> min;
				pToE545->setLimitsMin(1, min);
			}
			if (choice1 == "yMax"){
				cout << "yMax = ";
				cin >> max;
				pToE545->setLimitsMax(2, max);
			}
			if (choice1 == "yMin"){
				cout << "yMin = ";
				cin >> min;
				pToE545->setLimitsMin(2, min);
			}

			if (choice1 == "zMax"){
				cout << "zMax = ";
				cin >> max;
				pToE545->setLimitsMax(3, max);
			}
			if (choice1 == "zMin"){
				cout << "zMin = ";
				cin >> min;
				pToE545->setLimitsMin(3, min);
			}

		}	
}
void menu::mainMenu(){

	//////////////////////////////////////////////////////////////////////////////////////////////
	//Needed for making sure that program detects only key press when window is selected by user//
	//////////////////////////////////////////////////////////////////////////////////////////////

	//Get the handle to the console window
	HWND WINAPI handleToConsole = GetConsoleWindow();
	//Get handle to active window
	HWND WINAPI handleToActiveWindow;
	bool windowActive = 1;

	/////////////////////////////////////////////////////////////////////////////////////

	std::cout << fixed;
	std::cout << setprecision(3);

	//////////////////////////////////////////////////////////////////////////////////////
	//http://msdn.microsoft.com/en-us/library/windows/desktop/dd375731%28v=vs.85%29.aspx
	//////////////////////////////////////////////////////////////////////////////////////

	while (!(GetKeyState(VK_ESCAPE) & 0x8000))
	{
		////////////////////////////////////////////////////////////////////////////////////
		//Check if the consol handle is the same as the handl to the current active window//
		////////////////////////////////////////////////////////////////////////////////////
		handleToActiveWindow = GetForegroundWindow();

		if (handleToActiveWindow == handleToConsole){
			windowActive = 1;
		}
		else
		{
			windowActive = 0;
		}

		
		if ((GetKeyState(0x48) & 0x8000) && windowActive){
			helpMenu();
			Sleep(500);
			cout << "---------------Back in Main--------------" << endl;
		}


		//////////////////////////////////////////////////////////////////////////////////////
		//s for (s)ettingsMenu																		//
		//////////////////////////////////////////////////////////////////////////////////////
		if ((GetKeyState(0x53) & 0x8000) && (GetKeyState(0x30) & 0x8000) && windowActive){
			settingsMenu();
			cout << "---------------Back in Main--------------" << endl;
		}


		//l sets limits for threshold triggering
		if ((GetKeyState(0x4C) & 0x8000) && (GetKeyState(0x30) & 0x8000) && windowActive)
		{
			setLimitsMenu();
			cout << "---------------Back in Main--------------" << endl;			
		}

		moveUsingArrowsMenu(windowActive);
		controlVelocitiesMenu(windowActive);

		//p (p)rint
		if ((GetKeyState(0x50) & 0x8000) && (GetKeyState(0x30) & 0x8000) && windowActive){
			printMenu();
			cout << "---------------Back in Main--------------" << endl;
		}

		//Control + Enter = Open  or Close
		if ((GetKeyState(0x0D) & 0x8000) && (GetKeyState(0x30) & 0x8000) && windowActive)
		{
			openShutterMenu();
			cout << "---------------Back in Main--------------" << endl;
		}//Control + Enter = Open  or Close

		//Entf + Enter = Open or Close pulsed
		if ((GetKeyState(0x0D) & 0x8000) && (GetKeyState(0x2E) & 0x8000) && windowActive)
		{
			openShutterPulsedMenu();
			cout << "---------------Back in Main--------------" << endl;
		}

		//t = moveTo
		if ((GetKeyState(0x54) & 0x8000) && (GetKeyState(0x30) & 0x8000) && windowActive)
		{
			moveToMenu();
			cout << "---------------Back in Main--------------" << endl;
		}

		//c cut 
		if ((GetKeyState(0x43) & 0x8000) && (GetKeyState(0x30) & 0x8000) && windowActive)
		{
			cutMainMenu();
			cout << "---------------Back in Main--------------" << endl;
		}

		//f focus 
		if ((GetKeyState(0x46) & 0x8000) && (GetKeyState(0x30) & 0x8000) && windowActive)
		{
			//Just clearing the current command line
			const int KEYEVENT_KEYUP = 0x02;
			keybd_event(VK_ESCAPE, 0, 0, 0);              // press the Esc key
			keybd_event(VK_ESCAPE, 0, KEYEVENT_KEYUP, 0); // let up the Esc key

			pToE545->move(pToE545->itsXFocus, pToE545->itsYFocus, pToE545->itsZFocus);
			cout << "press any key for getting back to 100, 100 ,100" << endl;
			getchar();
			pToE545->moveTo(100, 100, 100);
			cout << "---------------Back in Main--------------" << endl;
		}


	}//while ESC is not pressed
}











