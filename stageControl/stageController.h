#pragma once
#include "Header.h"

//./ because I do not add the header to the project as I will not modify it, hence I have to give the relative path to the header.
#include "./PI_stuff/Pi_GCS2_DLL.h" 

class stageController
{

private: double Position[3];
		 
public:
	//Variables
	int ID;
	char szErrorMesage[1024];
	int	iError;
	char szAxes[17];

	//Methods

	///////////////////
	// Initialization//
	///////////////////
	void initialize();
	
	////////////////////////////////////////////////////////////////////
	// connect to the E-517 over RS-232 (COM port 1, baudrate 38400). //
	////////////////////////////////////////////////////////////////////
	int establishConnection();
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
	int switchChannelsOn();
	

	///////////////////////////////////////////
	//// close the servo loop (closed-loop). //
	///////////////////////////////////////////
	int switchAllServosOn();

	///////////////////////////////////////////
	//// move to coordinates	(closed-loop)//
	///////////////////////////////////////////
	//uses waitUntilMoveFinished();          
	void moveTo(double xCoord, double yCoord, double zCoord);

	///////////////////////////////////////////
	//// relative movement   	(closed-loop)//
	///////////////////////////////////////////        
	void move(double xDelta, double yDelta, double zDelta);

	void printPosition();
	void getPositon(double position[3]);

	///////////////////////////////////////////
	//// set velocity			(closed-loop)//
	///////////////////////////////////////////
	void setVelocity(double xVelocity, double yVelocity, double zVelocity);
	void setVelocity(const double velocity[3]);
	void getVelocity(double &xVelocity, double &yVelocity, double &zVelocity);
	void getVelocity(double velocity[3]);
	void printVelocity();

	///////////////////////////////////////////////////////
	//// change velocity by the delta values(closed-loop)//
	///////////////////////////////////////////////////////
	void deltaVelocity(double xDeltaVelocity, double yDeltaVelocity, double zDeltaVelocity);

	////////////////////////////////////////////////
	//// Wait until the closed loop move is done. //
	////////////////////////////////////////////////
	void waitUntilMoveFinished();


	/////////////////////////////////////////////////////////////////////////
	//// Both VCM and DCM have to be activated before using setVelocity	   //
	/////////////////////////////////////////////////////////////////////////
	int switchVelocityControlModeOn();
	int switchDriftControlModeOn();

	void minMaxTrigger(int xYorZaxis, double minimum, double maximum);
	void setTriggerMode(int axis, int mode);
	
	stageController();
	~stageController();
};

