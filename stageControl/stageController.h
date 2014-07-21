#pragma once
#include "Header.h"
#include "usefulFunctions.h"

//./ because I do not add the header to the project as I will not modify it, hence I have to give the relative path to the header.
#include "./PI_stuff/Pi_GCS2_DLL.h" 

class stageController
{

private: double Position[3];
		 usefulFunctions useful;
		 double veloLimit=9900;
		 
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
	bool establishConnection();
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
	bool switchChannelsOn();
	

	///////////////////////////////////////////
	//// close the servo loop (closed-loop). //
	///////////////////////////////////////////
	bool switchAllServosOn();

	///////////////////////////////////////////
	//// move to coordinates	(closed-loop)//
	///////////////////////////////////////////
	//uses waitUntilMoveFinished();          
	void moveTo(double xCoord, double yCoord, double zCoord);
	void moveTo(const double coordArray[3]);

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
	bool switchVelocityControlModeOn();
	bool switchDriftControlModeOn();

	void setTriggerMode(int axis, int mode);
	void setLimits(int xYorZaxis, double min, double max);
	void getLimits(int whichAxis, double &min, double &max);
	void getLimits(double &xMin, double &xMax, double &yMin, double &yMax, double &zMin, double &zMax);
	void printLimits();
	bool checkIfAnyLimit();
	void getConfigOfTriggerOutput();

	
	void openShutter();
	void closeShutter();

	template<int a, int b> void cutRel(double(&myarray)[a][b],double velo);
	
	void cutRel(double * pRelCoordArray);
	
	stageController();
	~stageController();
};

