// FirstSteps.cpp : Sample Program to demonstrate
//					- open loop motion
//                  - closed loop motion with referencing
//
//				make sure the Pi_gcs2_dll.h and the PI_GCS2_DLL.lib files are in the same directory or accessible via 
//              project settings
//              during runtime, the PI_GCS2_DLL.dll must be in the execution or search path

#include <conio.h>
#include <stdio.h>
#include <windows.h>
//./ because I do not add the header to the project as I will not modify it, hence I have to give the relative path to the header.
#include "./PI_stuff/Pi_GCS2_DLL.h" 
int main(int argc, char* argv[])
{
	BOOL bRtoSuccess;
	int ID;
	char szErrorMesage[1024];
	int	iError;



	////////////////////////////////////////////////////////////////////
	// connect to the E-517 over RS-232 (COM port 1, baudrate 38400). //
	////////////////////////////////////////////////////////////////////
	ID = PI_ConnectRS232 (1, 115200);
	if (ID<0)
	{
		iError = PI_GetError(ID);
		PI_TranslateError(iError, szErrorMesage, 1024);
		printf("ConnectRS232: ERROR %d: %s\n", iError, szErrorMesage);
		return(1);
	}
   


	/////////////////////////////////////////
	// Get the name of the connected axis. //
	/////////////////////////////////////////
	char szAxes[17];
	if (!PI_qSAI(ID, szAxes, 16))
	{
		iError = PI_GetError(ID);
		PI_TranslateError(iError, szErrorMesage, 1024);
		printf("SAI?: ERROR %d: %s\n", iError, szErrorMesage);
		PI_CloseConnection(ID);
		return(1);
	}
	printf(">SAI?:\n%s\n", szAxes);



	///////////////////////////////////////////////
	// Switch the piezo channels to online mode. //
	///////////////////////////////////////////////
	int iChnl[3];
	int iVal[3];

	// select the desired piezo channels to change.
	iChnl[0] = 1;
	iChnl[1] = 2;
	iChnl[2] = 3;

	// select the corresponding online mode (1 = online, 0 = offline).
	iVal[0] = 1;
	iVal[1] = 1;
	iVal[2] = 1;

	// Call the ONLine mode command
	if(!PI_ONL(ID, iChnl, iVal, 3/*number of piezo channel to change (array size)*/))
	{
		iError = PI_GetError(ID);
		PI_TranslateError(iError, szErrorMesage, 1024);
		printf("ONL: ERROR %d: %s\n", iError, szErrorMesage);
		PI_CloseConnection(ID);
		return(1);
	}
	printf(">ONL 1 1 2 1 3 1\n\n");



	/////////////////////////////////////////
	// close the servo loop (closed-loop). //
	/////////////////////////////////////////
	BOOL bFlags[3];

	// Switch on the Servo for all axes
	bFlags[0] = TRUE; // servo on for first axis in the string 'axes'.
	bFlags[1] = TRUE; // servo on for second axis in the string 'axes'.
	bFlags[2] = TRUE; // servo on for third axis in the string 'axes'.

	// call the SerVO mode command.
	if(!PI_SVO(ID, szAxes, bFlags))
	{
		iError = PI_GetError(ID);
		PI_TranslateError(iError, szErrorMesage, 1024);
		printf("SVO: ERROR %d: %s\n", iError, szErrorMesage);
		PI_CloseConnection(ID);
		return(1);
	}
	printf(">SVO A 1 B C 3 1\n\n");



	////////////////////////////////
	// Now you can move the axes. //
	////////////////////////////////
	double dPos[3];

	// move all axes the corresponding position in 'dPos'
	dPos[0] = 2.0; // mov first axis in the string 'axes' to position 2.0
	dPos[1] = 1.0; // mov second axis in the string 'axes' to position 1.0
	dPos[2] = 0.5; // mov third axis in the string 'axes' to position 0.5

	// call the MOV command (for closed servo loop).
	if(!PI_MOV(ID, szAxes, dPos))
	{
		iError = PI_GetError(ID);
		PI_TranslateError(iError, szErrorMesage, 1024);
		printf("MOV: ERROR %d: %s\n", iError, szErrorMesage);
		PI_CloseConnection(ID);
		return(1);
	}
	printf(">MOV 1 2.0 2 1.0 3 0.5\n\n");



	//////////////////////////////////////////////
	// Wait until the closed loop move is done. //
	//////////////////////////////////////////////
	BOOL bIsMoving[3];
	bIsMoving[0] = TRUE;
	while(bIsMoving[0] == TRUE)
	{
		////////////////////////////////////////////
		// get the current possition of all axes. //
		////////////////////////////////////////////

		//dPos[0] receives the position of the first axis in the string 'axes'.
		//dPos[1] receives the position of the second axis in the string 'axes'.
		//dPos[2] receives the position of the third axis in the string 'axes'.

		// call the command to querry the current POSition of axes.
		if(!PI_qPOS(ID, szAxes, dPos))
		{
			iError = PI_GetError(ID);
			PI_TranslateError(iError, szErrorMesage, 1024);
			printf("POS?: ERROR %d: %s\n", iError, szErrorMesage);
			PI_CloseConnection(ID);
			return(1);
		}


		////////////////////////////////////////
		// Read the moving state of the axes. //
		////////////////////////////////////////

		// if 'axes' = NULL or 'axis' is empty a general moving state of all axes ist returnd in 'bIsMoving[0]'
		// if 'bIsMoving[0]' = TRUE at least one axis of the controller ist still moving.
		// if 'bIsMoving[0]' = FALSE no axis of the contrller is moving.

		// if 'axes != NULL and 'axis' is not empty the moving state of every axis in 'axes' is returned in
		// the arry bIsMoving.
		if(!PI_IsMoving(ID, NULL /*axes = NULL*/, bIsMoving))
		{
			iError = PI_GetError(ID);
			PI_TranslateError(iError, szErrorMesage, 1024);
			printf("IsMoving: ERROR %d: %s\n", iError, szErrorMesage);
			PI_CloseConnection(ID);
			return(1);
		}

		printf(">POS?: \nA = %g\nB = %g\nC = %g\n\n", dPos[0], dPos[1], dPos[2]);
	}

    PI_CloseConnection(ID);
	_getch();
	return 0;
}
