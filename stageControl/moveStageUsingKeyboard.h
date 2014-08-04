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
//v				velocitstepSize[1]
//enter			shutter OPEN CLOSE


//del+	enter   open shutter for pulseDuration 
//pulseDuration can be adjusted in stepSize Menue 0+s

//4-1			velocity x Axis
//5-2			velocity y Axis
//6-3			velocity z Axis
//left-right	postion x Axis
//up-down		postion y Axis




void setDefaultValues(double stepSize[3], double velStepSize[3], double & pulseDuration, double & sleepValue){

	stepSize[0] = 1;
	stepSize[1] = 1;
	stepSize[2] = 1;

	velStepSize[0] = 1;
	velStepSize[1] = 1;
	velStepSize[2] = 1;

	sleepValue = 50;
	pulseDuration = 100;

}

void setMenu(double stepSize[3], double velStepSize[3], double & pulseDuration, usefulFunctions & useful, stageController & E545){

	//Just clearing the current command line
	const int KEYEVENT_KEYUP = 0x02;
	keybd_event(VK_ESCAPE, 0, 0, 0);              // press the Esc key
	keybd_event(VK_ESCAPE, 0, KEYEVENT_KEYUP, 0); // let up the Esc key

	string choice;
	cout << "Set..." << endl;
	cout << "stepSize for axis press (x), (y) or (z) or (a)" << endl;
	cout << "velocity step size (vx), (vy), (vz) or (v)" << endl;
	cout << "adjust shutter(p)ulse duration" << endl;
	cin >> choice;

	//axis Step Size 
	if (choice == "a"){
		cout << "xStepSize = ";
		useful.cinAndCheckForDoubleAndLimits(stepSize[0]);
		useful.cinAndCheckForDoubleAndLimits(stepSize[1]);
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
		cout << "yStepSize = ";
		useful.cinAndCheckForDoubleAndLimits(stepSize[1]);
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

	//pulse Duration
	if (choice == "p"){
		cout << "pulse duration = ";
		useful.cinAndCheckForDoubleAndLimits(pulseDuration,0);
	}


	cout << "---------------Back in Main--------------" << endl;
	

}

