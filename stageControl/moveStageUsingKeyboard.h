#pragma once
#include "Header.h"
#include "usefulFunctions.h"
#include "stageController.h"
#include "figures.h"

using namespace std;

//0+...
//p				print
//s				stepSize
//l				limits
//t				moveTo (t)arget
//c				cut 
//v				velocityStepsize
//enter			shutter OPEN CLOSE


//del+	enter   open shutter for pulseDuration 
//pulseDuration can be adjusted in stepSize Menue 0+s

//4-1			velocity x Axis
//5-2			velocity y Axis
//6-3			velocity z Axis
//left-right	postion x Axis
//up-down		postion y Axis



void moveStageUsingKeyboard(stageController &E545){

	usefulFunctions useful;

	figures::rectangle rectangle(E545);
	figures::polygon   polygon(E545);
	figures::surfaceRectangle surfaceRectangle(E545);



	//Get the handle to the console window
	HWND WINAPI handleToConsole=GetConsoleWindow();
	//Get handle to active window
	HWND WINAPI handleToActiveWindow;

	bool windowActive = 1;

	double xStepSize = 1;
	double yStepSize = 1;

	double xVelocityStepSize = 1;
	double yVelocityStepSize = 1;

	

	int sleepValue = 50;

	int pulseDuration = 200;

	std::cout << fixed;
	std::cout << setprecision(3);

	
	//http://msdn.microsoft.com/en-us/library/windows/desktop/dd375731%28v=vs.85%29.aspx
	while (!(GetKeyState(VK_ESCAPE) & 0x8000))
	{

		//Check is consol window is active
		handleToActiveWindow = GetForegroundWindow();
		if (handleToActiveWindow == handleToConsole){
			windowActive = 1;
		}
		else
		{
			windowActive = 0;
		}


		//////////////////////////////////////////////
		//				Positions					//
		//////////////////////////////////////////////

		//left
		while ((GetKeyState(0x25) & 0x8000) &&windowActive)
		{
			E545.move(-1.0*xStepSize, 0, 0);
			E545.printPosition();
			Sleep(sleepValue);
		}//left

		//right
		while ((GetKeyState(0x27) & 0x8000) && windowActive)
		{
			E545.move(1.0*xStepSize, 0, 0);
			E545.printPosition();
			Sleep(sleepValue);
		}//right

		//down
		while ((GetKeyState(0x28) & 0x8000) && windowActive)
		{
			E545.move(0, -1.0*yStepSize, 0);
			E545.printPosition();
			Sleep(sleepValue);
		}//down

		//up
		while ((GetKeyState(0x26) & 0x8000) && windowActive)
		{
			E545.move(0, 1.0*yStepSize, 0);
			E545.printPosition();
			Sleep(sleepValue);
		}//up


		//////////////////////////////////////////////
		//				VELOCITIES					//
		//////////////////////////////////////////////

		//x-Achse Velocity +  == 4
		while ((GetKeyState(0x64) & 0x8000) && windowActive)
		{
			E545.deltaVelocity(xVelocityStepSize, 0, 0);
			E545.printVelocity();
			Sleep(sleepValue);
		}//4

		//x-Achse Velocity - == 1
		while ((GetKeyState(0x61) & 0x8000) && windowActive)
		{
			E545.deltaVelocity(-1.0*xVelocityStepSize, 0, 0);
			E545.printVelocity();
			Sleep(sleepValue);
		}//1

		//y-Achse Velocity +  == 5
		while ((GetKeyState(0x65) & 0x8000) && windowActive)
		{
			E545.deltaVelocity(0, yVelocityStepSize, 0);
			E545.printVelocity();
			Sleep(sleepValue);

		}//5

		//y-Achse Velocity - ==2
		while ((GetKeyState(0x62) & 0x8000) && windowActive)
		{
			E545.deltaVelocity(0, -1.0*yVelocityStepSize, 0);
			E545.printVelocity();
			Sleep(sleepValue);
		}//2


		//////////////////////////////////////////////
		//				Print   					//
		//////////////////////////////////////////////

		//p print current position or velocity or limits
		if ((GetKeyState(0x50) & 0x8000) && (GetKeyState(0x30) & 0x8000) && windowActive){

			//Just clearing the current command line
			const int KEYEVENT_KEYUP = 0x02;
			keybd_event(VK_ESCAPE, 0, 0, 0);              // press the Esc key
			keybd_event(VK_ESCAPE, 0, KEYEVENT_KEYUP, 0); // let up the Esc key

			char choice;
			cout << "print (p)position, (v)velocities or (l)imits?" << endl;
			cin >> choice;


			if (choice == 'p')
			{
				E545.printPosition();
			}

			if (choice == 'v')
			{
				E545.printVelocity();
			}

			if (choice == 'l')
			{
				E545.printLimits();
			}


			
		}//if p

		//////////////////////////////////////////////
		//				step size					//
		//////////////////////////////////////////////

		//s for stepSize
		if ((GetKeyState(0x53) & 0x8000) && (GetKeyState(0x30) & 0x8000) && windowActive){

			//Just clearing the current command line
			const int KEYEVENT_KEYUP = 0x02;
			keybd_event(VK_ESCAPE, 0, 0, 0);              // press the Esc key
			keybd_event(VK_ESCAPE, 0, KEYEVENT_KEYUP, 0); // let up the Esc key

			char choice;
			bool success = 0;
			cout << "Set stepSize press x or y or adjust shutter pulse duration" << endl;
			cin >> choice;

			if (choice == 'x'){

				cout << "xStepSize = ";
				useful.cinAndCheckForDoubleAndLimits(xStepSize);

			}

			if (choice == 'y'){
				cout << "yStepSize = ";
				useful.cinAndCheckForDoubleAndLimits(yStepSize);
			}

			if (choice == 's'){
				cout << "pulse duration = ";
				cin >> pulseDuration;
			}
			cout << "---------------Back in Main--------------" << endl;
		}//s

		//v for velocityStepSize
		if ((GetKeyState(0x56) & 0x8000) && (GetKeyState(0x30) & 0x8000) && windowActive){

			//Just clearing the current command line
			const int KEYEVENT_KEYUP = 0x02;
			keybd_event(VK_ESCAPE, 0, 0, 0);              // press the Esc key
			keybd_event(VK_ESCAPE, 0, KEYEVENT_KEYUP, 0); // let up the Esc key

			char choice;
			cout << "Set velocity stepSize press x or y" << endl;
			cin >> choice;
			if (choice == 'x'){
				cout << "xVelocityStepSize = ";
				useful.cinAndCheckForDoubleAndLimits(xVelocityStepSize);
			}
			if (choice == 'y'){
				cout << "yVelocityStepSize = ";
				useful.cinAndCheckForDoubleAndLimits(yVelocityStepSize);
			}
			cout << "---------------Back in Main--------------" << endl;
		}//v


		//l sets limits for threshold triggering
		if ((GetKeyState(0x4C) & 0x8000) && (GetKeyState(0x30) & 0x8000) && windowActive)
		{

			//Just clearing the current command line
			const int KEYEVENT_KEYUP = 0x02;
			keybd_event(VK_ESCAPE, 0, 0, 0);              // press the Esc key
			keybd_event(VK_ESCAPE, 0, KEYEVENT_KEYUP, 0); // let up the Esc key

			char choice0;
			string choice1;
			char choice2;
			double min;
			double max;

			E545.setTriggerMode(1, 3);
			E545.setTriggerMode(2, 3);
			E545.setTriggerMode(3, 3);

			cout << "set min max (s)eperately or set (l)limits" << endl;
			cin >> choice0;

			if (choice0 == 'l'){

				cout << "set limits, press x, y or z" << endl;
				cin >> choice1;

				if (choice1 == "x"){
					cout << "min = ";
					useful.cinAndCheckForDouble(min);
					cout << "max = ";
					useful.cinAndCheckForDouble(max);
					E545.setLimits(1, min, max);
				}
				if (choice1 == "y"){
					cout << "min = ";
					useful.cinAndCheckForDouble(min);
					cout << "max = ";
					useful.cinAndCheckForDouble(max);
					E545.setLimits(2, min, max);
				}
				if (choice1 == "z"){
					cout << "min = ";
					useful.cinAndCheckForDouble(min);
					cout << "max = ";
					useful.cinAndCheckForDouble(max);
					E545.setLimits(3, min, max);
				}
			}

			if (choice0 == 's'){

				cout << "set min or max, type xMax, xMin, yMin or yMax" << endl;
				cin >> choice1;

				if (choice1 == "xMax"){
					cout << "xMax = ";
					cin >> max;
					E545.setLimitsMax(1, max);
				}
				if (choice1 == "xMin"){
					cout << "xMin = ";
					cin >> min;
					E545.setLimitsMin(1, min);
				}
				if (choice1 == "yMax"){
					cout << "yMax = ";
					cin >> max;
					E545.setLimitsMax(2, max);
				}
				if (choice1 == "yMin"){
					cout << "yMin = ";
					cin >> min;
					E545.setLimitsMin(2, min);
				}

			}
			cout << "---------------Back in Main--------------" << endl;
		}//l


		//Control + Enter = Open  or Close
		if ((GetKeyState(0x0D) & 0x8000) && (GetKeyState(0x30) & 0x8000) && windowActive)
		{
			if (E545.checkIfAnyLimit()){
				E545.closeShutter();
			}
			else
			{
				E545.openShutter();
			}

			Sleep(5 * sleepValue);
		}//Control + Enter = Open  or Close

		//Entf + Enter = Open or Close pulsed
		if ((GetKeyState(0x0D) & 0x8000) && (GetKeyState(0x2E) & 0x8000) && windowActive)
		{
			if (E545.checkIfAnyLimit()){
				E545.closeShutter();
				Sleep(pulseDuration);
				E545.openShutter();

			}
			else
			{
				E545.openShutter();
				Sleep(pulseDuration);
				E545.closeShutter();
			}

			Sleep(5 * sleepValue);
		}//Entf + Enter = Open or Close pulsed

		//t = moveTo
		if ((GetKeyState(0x54) & 0x8000) && (GetKeyState(0x30) & 0x8000) && windowActive)
		{
			double target[3];
			cout << "moveTo" << endl;
			cout << "xTarget = ";
			useful.cinAndCheckForDouble(target[0]);
			cout << "yTarget = ";
			useful.cinAndCheckForDouble(target[1]);
			cout << "zTarget = ";
			useful.cinAndCheckForDouble(target[2]);

			E545.moveTo(target);
			E545.printPosition();

			cout << "---------------Back in Main--------------" << endl;
		}//t = moveTo

		//c = cut 
		if ((GetKeyState(0x43) & 0x8000) && (GetKeyState(0x30) & 0x8000) && windowActive)
		{
			//Just clearing the current command line
			const int KEYEVENT_KEYUP = 0x02;
			keybd_event(VK_ESCAPE, 0, 0, 0);              // press the Esc key
			keybd_event(VK_ESCAPE, 0, KEYEVENT_KEYUP, 0); // let up the Esc key

			char choice1;
			cout << "n for set up (n)ew figure and (c) for cut:" << endl;
			cin >> choice1;


			if (choice1 == 'n'){
				char choice2;
				cout << "Set up new figure:" << endl;
				cout << "(r)ectangle" << endl;
				cout << "(p)olygon" << endl;
				cout << "(s)urface Rectangle" << endl;
				cin >> choice2;

				if (choice2 == 'r'){
					double a, b, phi0, velo;
					cout << "a = " << endl;
					cin >> a;
					cout << "b = " << endl;
					cin >> b;
					cout << "phi0 = " << endl;
					cin >> phi0;
					cout << "velocity = " << endl;
					cin >> velo;

					rectangle.set(a, b, phi0, velo);
				}

				if (choice2 == 'p'){
					double R, phi0, velo;
					int steps;
					cout << "R = " << endl;
					cin >> R;
					cout << "phi0 = " << endl;
					cin >> phi0;
					cout << "steps = " << endl;
					cin >> steps;
					cout << "velocity = " << endl;
					cin >> velo;
					polygon.set(R, phi0, steps, velo);
				}

				if (choice2 == 's'){
					double a, b, phi0, velo;
					int resolution;
					cout << "a = " << endl;
					cin >> a;
					cout << "b = " << endl;
					cin >> b;
					cout << "phi0 = " << endl;
					cin >> phi0;
					cout << "resolution = " << endl;
					cin >> resolution;
					cout << "velocity = " << endl;
					cin >> velo;
					surfaceRectangle.set(a, b, phi0, velo, resolution, 'l');
				}
				cout << "---------------Back in Main--------------" << endl;
			}

			if (choice1 == 'c'){

				string choice2;
				cout << "Choose figure to cut:" << endl;
				cout << "------------rectangle------------"<<endl;
				cout << "(rRel)"	<<endl;
				cout << "(rAbs)" << endl;
				cout << "------------polygon------------" << endl;
				cout << "(pAbs)" <<endl;
				cout << "(pRel)" << endl;
				cout << "(pA) = predfined values pAbs" << endl;
				cout << "(p)  = pAbs with pre. def. values but velocity can be set" << endl;
				cout << "(pR) = pRel but predefinied values" << endl;
				cout << "------------area------------" << endl;
				cout << "(sRel)" << endl;
				cout << "(sAbs)" << endl;

				cin >> choice2;

				if (choice2 == "rRel"){
					rectangle.cutRel();
					cout << "---------------Back in Main--------------" << endl;
				}

				if (choice2 == "rAbs"){
					rectangle.cutAbs();
					cout << "---------------Back in Main--------------" << endl;
				}

				if (choice2 == "rAbsLim"){
					rectangle.cutAbsLim();
					cout << "---------------Back in Main--------------" << endl;
				}


				if (choice2 == "pRel"){
					polygon.cutRel();
					cout << "---------------Back in Main--------------" << endl;
				}

				if (choice2 == "pAbs"){
					polygon.cutAbs();
					cout << "---------------Back in Main--------------" << endl;
				}

				if (choice2 == "sRel"){
					surfaceRectangle.cutRel();
					cout << "---------------Back in Main--------------" << endl;
				}

				if (choice2 == "sAbs"){
					surfaceRectangle.cutAbs();
					cout << "---------------Back in Main--------------" << endl;
				}

				if (choice2 == "pR"){
					polygon.set(15, 0, 20, 1000);
					polygon.cutRel();
					cout << "---------------Back in Main--------------" << endl;
				}

				if (choice2 == "pA"){
					polygon.set(15, 0, 10, 1000);
					polygon.cutAbs();
					cout << "---------------Back in Main--------------" << endl;
				}

				if (choice2 == "p"){
					double vel = 0;
					double steps = 0;
					double R = 0;

					cout << "Press Escape for returning to main menu" << endl;

					while (!(GetKeyState(0x51) & 0x8000) && !(GetKeyState(VK_ESCAPE) & 0x8000))
					{


						//page Up
						while ((GetKeyState(0x21) & 0x8000))
						{
							R = R + 1;
							cout << "R = " << R << endl;
							Sleep(sleepValue*2);
						}//page Up

						//Page Down
						while ((GetKeyState(0x22) & 0x8000))
						{
							R = R - 1;
							cout << "R = " << R << endl;
							Sleep(sleepValue*2);
						}//Page Down

						//down
						while ((GetKeyState(0x28) & 0x8000))
						{
							vel = vel - 100;
							cout << "vel = " << vel << endl;
							Sleep(sleepValue);
						}//down

						//up
						while ((GetKeyState(0x26) & 0x8000))
						{
							vel = vel + 100;
							cout << "vel = " << vel << endl;
							Sleep(sleepValue);
						}//up

						//left
						while ((GetKeyState(0x25) & 0x8000))
						{
							steps = steps - 1;
							cout << "steps = " << steps << endl;
							Sleep(sleepValue);
						}//left

						//right
						while ((GetKeyState(0x27) & 0x8000))
						{
							steps = steps + 1;
							cout << "steps = " << steps << endl;
							Sleep(sleepValue);
						}//right

						if ((GetKeyState(0x43) & 0x8000))
						{
							polygon.set(R, 0, steps, vel);
							polygon.cutAbs();

						}
					}
					Sleep(sleepValue * 5);
					
				}
				cout << "---------------Back in Main--------------" << endl;
			}


		}//c = cut 

		


	}//while ESC is not pressed

}//moveStageUsingKeyboard