#pragma once
#include "Header.h"
#include "usefulFunctions.h"

//./ because I do not add the header to the project as I will not modify it, hence I have to give the relative path to the header.
#include "./PI_stuff/Pi_GCS2_DLL.h" 
#include <Eigen/Core>

class stageController
{

private: double Position[3];
		 usefulFunctions useful;
		 double  veloLimit;

		 string fileName_FocusValues = "focusValues.txt";
		 
		 
public:
	//Variables
	double itsXFocus, itsYFocus, itsZFocus;
	int ID;
	char szErrorMesage[1024];
	int	iError;
	char szAxes[17];

	//Methods

	///////////////////
	// Initialization//
	///////////////////
	void initialize();

	void setFocus_and_writeValuesToFile(double xFocus, double yFocus, double zFocus);
	void loadFocusValuesFromFile();
	void moveInFocus();
	int getID();
	void printMemberVariables(){

		cout << "ID = " << "\t" << ID << endl;
		cout << "itsXFocus = " << "\t" << itsXFocus << endl;
		cout << "itsYFocus = " << "\t" << itsYFocus << endl;
		cout << "itsZFocus = " << "\t" << itsZFocus << endl;

	}
	
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
	void move(double vec[3]);

	void printPosition();
	void getPositon(double position[3]);
	void getPositon(Eigen::Vector3d & position);

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
	void setLimitsMin(int whichAxis, double min);
	void setLimitsMax(int whichAxis, double max);

	string setLimitsMacro(int whichAxis, double value1, double value2, double altValue1, double altValue2);

	void getLimits(int whichAxis, double &min, double &max);
	void getLimits(double &xMin, double &xMax, double &yMin, double &yMax, double &zMin, double &zMax);
	void printLimits();

	bool checkIfAnyLimit();
	void getConfigOfTriggerOutput();

	void sendMacros(string nameOfFile);
	void startMacroAndWaitWhileRunning(string nameOfmacro);
	void startMacro(string nameOfmacro);
	
	void openShutter();
	void closeShutter();

	stageController();
	~stageController();
};

