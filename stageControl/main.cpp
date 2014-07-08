// FirstSteps.cpp : Sample Program to demonstrate
//					- open loop motion
//                  - closed loop motion with referencing
//
//				make sure the Pi_gcs2_dll.h and the PI_GCS2_DLL.lib files are in the same directory or accessible via 
//              project settings
//              during runtime, the PI_GCS2_DLL.dll must be in the execution or search path

#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <string>
//./ because I do not add the header to the project as I will not modify it, hence I have to give the relative path to the header.
#include "./PI_stuff/Pi_GCS2_DLL.h" 
#include "stageControler.h"
using namespace std;

int main(int argc, char* argv[])
{
	stageControler E545;
	E545.printNameOfConnectedAxis();
	E545.establishConnection();
	E545.printNameOfConnectedAxis();
	E545.switchChannelsOn();
	E545.switchAllServosOn();
	E545.switchVelocityControlModeOn();
	E545.switchDriftControlModeOn();
	Sleep(1);

	E545.minMaxTrigger(1, 50, 150);
	E545.setVelocity(100, 100, 100);
	E545.moveTo(0, 0, 0);

	double xVelocity;
	while (!(GetKeyState(0x51) & 0x8000) && !(GetKeyState(VK_ESCAPE) & 0x8000))
	{
		cout << "Velocity it will go to 200?" << endl;
		cin >> xVelocity;
		E545.setVelocity(xVelocity, 100, 100);
		E545.moveTo(200, 0, 0);

		cout << "Velocity it will go to 0?" << endl;
		cin >> xVelocity;
		E545.setVelocity(xVelocity, 100, 100);
		E545.moveTo(0, 0, 0);
	}
	E545.closeConnection();

	return 0;
}
