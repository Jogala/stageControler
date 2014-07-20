// FirstSteps.cpp : Sample Program to demonstrate
//					- open loop motion
//                  - closed loop motion with referencing
//
//				make sure the Pi_gcs2_dll.h and the PI_GCS2_DLL.lib files are in the same directory or accessible via 
//              project settings
//              during runtime, the PI_GCS2_DLL.dll must be in the execution or search path


//./ because I do not add the header to the project as I will not modify it, hence I have to give the relative path to the header.
#include "Header.h"
#include "./PI_stuff/Pi_GCS2_DLL.h" 
#include "cut.h"
#include "moveStageUsingKeyboard.h"
#include "figures.h"
using namespace std;




int main(int argc, char* argv[])
{


	//Initialization
	//Default is 	setVelocity(50, 50, 50); moveTo(100, 100, 100);
	stageController E545;
	E545.initialize();
	moveStageUsingKeyboard(E545);

	E545.closeConnection();

	


}






