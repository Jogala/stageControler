// FirstSteps.cpp : Sample Program to demonstrate
//					- open loop motion
//                  - closed loop motion with referencing
//
//				make sure the Pi_gcs2_dll.h and the PI_GCS2_DLL.lib files are in the same directory or accessible via 
//              project settings
//              during runtime, the PI_GCS2_DLL.dll must be in the execution or search path


//./ because I do not add the header to the project as I will not modify it, hence I have to give the relative path to the header.
#include "Header.h"
#include "./PI_stuff/PI_GCS2_DLL.h" 
#include "moveStageUsingKeyboard.h"
#include "figures.h"
#include "figuresWriteCoordToFile.h"
#include "menu.h"
using namespace std;


int main(int argc, char* argv[])
{

	////Initialization
	////Default is 	setVelocity(50, 50, 50); moveTo(100, 100, 100);
	//stageController E545;
	//E545.initialize();
	//menu menu(E545);
	//menu.mainMenu();



	////int ID = E545.getID();
	//
	////cout << PI_GcsCommandset(ID, "CTO 1 6 40 1 5 20") << endl;
	////while (!(GetKeyState(VK_ESCAPE) & 0x8000))
	////{
	////	cout << PI_GcsCommandset(ID, "CTO 1 5 20 1 6 40") << endl;
	////	Sleep(100);
	////	cout << PI_GcsCommandset(ID, "CTO 1 6 140 1 5 120") << endl;
	////	Sleep(100);
	////}


	////E545.setLimits(1, 40, 20);
	////while (!(GetKeyState(VK_ESCAPE) & 0x8000))
	////{
	////	cout << "beliebige Taste um Limits zu 20-40 zu setzen" << endl;
	////	getchar();
	////	E545.setLimits(1, 20, 40);
	////	cout << "limits set:" << endl;
	////	E545.printLimits();
	////	Sleep(100);
	////	cout << "beliebige Taste um Limits zu 120-140 zu setzen" << endl;
	////	getchar();
	////	E545.setLimits(1, 140, 120);
	////	cout << "limits set:" << endl;
	////	E545.printLimits();
	////	Sleep(100);
	////}



	//E545.closeConnection();



}






