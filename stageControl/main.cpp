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
	
	while (1){
		E545.moveTo(0, 0, 0);
		Sleep(3000);
		E545.moveTo(200, 200, 200);
		Sleep(3000);
	}

	E545.closeConnection();
	
	
	










	







	////////////////////////////////////////////////
	//// Wait until the closed loop move is done. //
	////////////////////////////////////////////////
	//BOOL bIsMoving[3];
	//bIsMoving[0] = TRUE;
	//while(bIsMoving[0] == TRUE)
	//{
	//	////////////////////////////////////////////
	//	// get the current possition of all axes. //
	//	////////////////////////////////////////////

	//	//Position[0] receives the position of the first axis in the string 'axes'.
	//	//Position[1] receives the position of the second axis in the string 'axes'.
	//	//Position[2] receives the position of the third axis in the string 'axes'.

	//	// call the command to querry the current POSition of axes.
	//	if(!PI_qPOS(ID, szAxes, dPos))
	//	{
	//		iError = PI_GetError(ID);
	//		PI_TranslateError(iError, szErrorMesage, 1024);
	//		printf("POS?: ERROR %d: %s\n", iError, szErrorMesage);
	//		PI_CloseConnection(ID);
	//		return(1);
	//	}



	//	////////////////////////////////////////
	//	// Read the moving state of the axes. //
	//	////////////////////////////////////////

	//	// if 'axes' = NULL or 'axis' is empty a general moving state of all axes ist returnd in 'bIsMoving[0]'
	//	// if 'bIsMoving[0]' = TRUE at least one axis of the controller ist still moving.
	//	// if 'bIsMoving[0]' = FALSE no axis of the contrller is moving.

	//	// if 'axes != NULL and 'axis' is not empty the moving state of every axis in 'axes' is returned in
	//	// the arry bIsMoving.
	//	if(!PI_IsMoving(ID, NULL /*axes = NULL*/, bIsMoving))
	//	{
	//		iError = PI_GetError(ID);
	//		PI_TranslateError(iError, szErrorMesage, 1024);
	//		printf("IsMoving: ERROR %d: %s\n", iError, szErrorMesage);
	//		PI_CloseConnection(ID);
	//		return(1);
	//	}

	//	printf(">POS?: \nA = %g\nB = %g\nC = %g\n\n", dPos[0], dPos[1], dPos[2]);
	//}

 //   PI_CloseConnection(ID);
	

	return 0;
}
