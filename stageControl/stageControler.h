#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <string>

//./ because I do not add the header to the project as I will not modify it, hence I have to give the relative path to the header.
#include "./PI_stuff/Pi_GCS2_DLL.h" 

class stageControler
{

private: BOOL servosStatus[3];
		 double Position[3];

public:

	//Variables
	int ID;
	char szErrorMesage[1024];
	int	iError;
	char szAxes[17];

	//Methods
	
	////////////////////////////////////////////////////////////////////
	// connect to the E-517 over RS-232 (COM port 1, baudrate 38400). //
	////////////////////////////////////////////////////////////////////
	void establishConnection();
	//returns 0 in case of success, and 1 for failure

	////////////////////
	//Close Connection//
	////////////////////
	void closeConnection();

	/////////////////////////////////////////
	// Get the name of the connected axis. //
	/////////////////////////////////////////
	void printNameOfConnectedAxis();

	/////////////////////////////////////////////////
	//// Switch the piezo channels to online mode. //
	/////////////////////////////////////////////////
	void switchChannelsOn();

	///////////////////////////////////////////
	//// close the servo loop (closed-loop). //
	///////////////////////////////////////////
	void switchAllServosOn();

	///////////////////////////////////////////
	//// move to coordinates	(closed-loop)//
	///////////////////////////////////////////
	void moveTo(double xCoord, double yCoord, double zCoord);
	void moveTo(double coordArray[3]);

	////////////////////////////////////////////////
	//// Wait until the closed loop move is done. //
	////////////////////////////////////////////////

	
	
	
	stageControler();
	~stageControler();
};

