#pragma once
#include "Header.h"
#include "usefulFunctions.h"
#include "stageController.h"
#include "cut.h"

using namespace std;

//ctrl+...
//p				print
//s				shutter
//l				limits
//t				moveTo (t)arget
//f				cut (f)igure
//enter			shutter OPEN CLOSE

//4-1			velocity x Axis
//5-2			velocity y Axis
//6-3			velocity z Axis
//left-right	postion x Axis
//up-down		postion y Axis



void moveStageUsingKeyboard(stageController &E545){

	usefulFunctions useful;
	cut cut(E545);

	double xStepSize = 1;
	double yStepSize = 1;

	double xVelocityStepSize = 1;
	double yVelocityStepSize = 1;

	int sleepValue = 50;

	std::cout << fixed;
	std::cout << setprecision(3);

	//http://msdn.microsoft.com/en-us/library/windows/desktop/dd375731%28v=vs.85%29.aspx
	while (!(GetKeyState(0x51) & 0x8000) && !(GetKeyState(VK_ESCAPE) & 0x8000))
	{

		//////////////////////////////////////////////
		//				Positions					//
		//////////////////////////////////////////////

		//left
		while ((GetKeyState(0x25) & 0x8000))
		{
			E545.move(-1.0*xStepSize, 0, 0);
			E545.printPosition();
			Sleep(sleepValue);
		}//left

		//right
		while ((GetKeyState(0x27) & 0x8000))
		{
			E545.move(1.0*xStepSize, 0, 0);
			E545.printPosition();
			Sleep(sleepValue);
		}//right

		//down
		while ((GetKeyState(0x28) & 0x8000))
		{
			E545.move(0, -1.0*yStepSize, 0);
			E545.printPosition();
			Sleep(sleepValue);
		}//down

		//up
		while ((GetKeyState(0x26) & 0x8000))
		{
			E545.move(0, 1.0*yStepSize, 0);
			E545.printPosition();
			Sleep(sleepValue);
		}//up


		//////////////////////////////////////////////
		//				VELOCITIES					//
		//////////////////////////////////////////////

		//x-Achse Velocity +  == 4
		while ((GetKeyState(0x64) & 0x8000))
		{
			E545.deltaVelocity(xVelocityStepSize, 0, 0);
			E545.printVelocity();
			Sleep(sleepValue);
		}//4

		//x-Achse Velocity - == 1
		while ((GetKeyState(0x61) & 0x8000))
		{
			E545.deltaVelocity(-1.0*xVelocityStepSize, 0, 0);
			E545.printVelocity();
			Sleep(sleepValue);
		}//1

		//y-Achse Velocity +  == 5
		while ((GetKeyState(0x65) & 0x8000))
		{
			E545.deltaVelocity(0, yVelocityStepSize, 0);
			E545.printVelocity();
			Sleep(sleepValue);

		}//5

		//y-Achse Velocity - ==2
		while ((GetKeyState(0x62) & 0x8000))
		{
			E545.deltaVelocity(0, -1.0*yVelocityStepSize, 0);
			E545.printVelocity();
			Sleep(sleepValue);
		}//2


		//////////////////////////////////////////////
		//				Print   					//
		//////////////////////////////////////////////

		//p print current position or velocity or limits
		if ((GetKeyState(0x50) & 0x8000) && (GetKeyState(0x11) & 0x8000)){

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
		if ((GetKeyState(0x53) & 0x8000) && (GetKeyState(0x11) & 0x8000)){

			//Just clearing the current command line
			const int KEYEVENT_KEYUP = 0x02;
			keybd_event(VK_ESCAPE, 0, 0, 0);              // press the Esc key
			keybd_event(VK_ESCAPE, 0, KEYEVENT_KEYUP, 0); // let up the Esc key

			char choice;
			bool success = 0;
			cout << "Set stepSize press x or y" << endl;
			cin >> choice;

			if (choice == 'x'){

				cout << "xStepSize = ";
				useful.cinAndCheckForDoubleAndLimits(xStepSize);

			}

			if (choice == 'y'){
				cout << "yStepSize = ";
				useful.cinAndCheckForDoubleAndLimits(yStepSize);
			}
		}//s

		//v for velocityStepSize
		if ((GetKeyState(0x56) & 0x8000) && (GetKeyState(0x11) & 0x8000)){

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
		}//v


		//l sets limits for threshold triggering
		if ((GetKeyState(0x4C) & 0x8000) && (GetKeyState(0x11) & 0x8000))
		{

			//Just clearing the current command line
			const int KEYEVENT_KEYUP = 0x02;
			keybd_event(VK_ESCAPE, 0, 0, 0);              // press the Esc key
			keybd_event(VK_ESCAPE, 0, KEYEVENT_KEYUP, 0); // let up the Esc key

			char choice;
			double min;
			double max;

			E545.setTriggerMode(1, 3);
			E545.setTriggerMode(2, 3);
			E545.setTriggerMode(3, 3);

			cout << "set limits, press x or y" << endl;
			cin >> choice;

			if (choice == 'x'){
				cout << "min = ";
				useful.cinAndCheckForDouble(min);
				cout << "max = ";
				useful.cinAndCheckForDouble(max);
				E545.setLimits(1, min, max);
			}
			if (choice == 'y'){
				cout << "min = ";
				useful.cinAndCheckForDouble(min);
				cout << "max = ";
				useful.cinAndCheckForDouble(max);
				E545.setLimits(2, min, max);
			}
			if (choice == 'z'){
				cout << "min = ";
				useful.cinAndCheckForDouble(min);
				cout << "max = ";
				useful.cinAndCheckForDouble(max);
				E545.setLimits(3, min, max);
			}
		}//l


		//Control + Enter = Open  or Close
		if ((GetKeyState(0x0D) & 0x8000) && (GetKeyState(0x11) & 0x8000))
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

		//t = moveTo
		if ((GetKeyState(0x54) & 0x8000) && (GetKeyState(0x11) & 0x8000))
		{
			double target[3];
			cout << "moveTo, press (a)adavanced options: " << endl;
			cout << "xTarget = ";
			useful.cinAndCheckForDouble(target[0]);
			cout << "yTarget = ";
			useful.cinAndCheckForDouble(target[1]);
			cout << "zTarget = ";
			useful.cinAndCheckForDouble(target[2]);

			E545.moveTo(target);
			E545.printPosition();
		}//t = moveTo

		//f = cut (f)igure
		if ((GetKeyState(0x46) & 0x8000))
		{
			//Just clearing the current command line
			const int KEYEVENT_KEYUP = 0x02;
			keybd_event(VK_ESCAPE, 0, 0, 0);              // press the Esc key
			keybd_event(VK_ESCAPE, 0, KEYEVENT_KEYUP, 0); // let up the Esc key



		}//f = cut figure


	}//while ESC is not pressed

}//moveStageUsingKeyboard