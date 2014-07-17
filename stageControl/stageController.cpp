#include "stageController.h"

void stageController::initialize(){

	if (establishConnection())
	{
		printNameOfConnectedAxis();
		if (switchChannelsOn())
		{
			if (switchAllServosOn())
			{
				if (switchVelocityControlModeOn())
				{
					if (switchDriftControlModeOn())
					{
						setVelocity(50, 50, 50);
						moveTo(100, 100, 100);
						setTriggerMode(1, 3);
						setTriggerMode(2, 3);
						setTriggerMode(3, 3);
						setLimits(1, 0, 0);
						setLimits(2, 0, 0);
						setLimits(3, 0, 0);
						std::cout << "E545 ready" << std::endl;
					}
				}
			}
		}
	}


}
bool stageController::establishConnection(){
	ID = PI_ConnectRS232(1, 115200);
	if (ID < 0)
	{
		iError = PI_GetError(ID);
		PI_TranslateError(iError, szErrorMesage, 1024);
		printf("ConnectRS232: ERROR %d: %s\n", iError, szErrorMesage);
		return 0;
	}
	else{
		std::cout << "ID = " << ID << " connection established" << std::endl;
		return 1;
	}
}
void stageController::closeConnection(){

	PI_CloseConnection(ID);
	std::cout << "Connection closed" << std::endl;
}
void stageController::printNameOfConnectedAxis(){
	if (!PI_qSAI(ID, szAxes, 16))
	{
		iError = PI_GetError(ID);
		PI_TranslateError(iError, szErrorMesage, 1024);
		printf("SAI?: ERROR %d: %s\n", iError, szErrorMesage);
		PI_CloseConnection(ID);
	}
	else
	{
		std::string connectedAxis(szAxes);
		std::cout << "Connected Axis: " << std::endl << connectedAxis << std::endl;
	}

}
bool stageController::switchChannelsOn(){
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
	if (!PI_ONL(ID, iChnl, iVal, 3/*number of piezo channel to change (array size)*/))
	{
		iError = PI_GetError(ID);
		PI_TranslateError(iError, szErrorMesage, 1024);
		printf("ONL: ERROR %d: %s\n", iError, szErrorMesage);
		PI_CloseConnection(ID);
		return 0;
	}
	else
	{
		std::cout << "All channels online" << std::endl;
		return 1;
	}
}
//////////////////////////////////////////////////////
//					Move							//
//////////////////////////////////////////////////////
bool stageController::switchAllServosOn(){

	// Switch on the Servo for all axes
	BOOL servosStatus[3];
	servosStatus[0] = 1; // servo on for first axis in the string 'axes'.
	servosStatus[1] = 1; // servo on for second axis in the string 'axes'.
	servosStatus[2] = 1; // servo on for third axis in the string 'axes'.

	// call the SerVO mode command.
	if (!PI_SVO(ID, szAxes, servosStatus))
	{
		iError = PI_GetError(ID);
		PI_TranslateError(iError, szErrorMesage, 1024);
		printf("SVO: ERROR %d: %s\n", iError, szErrorMesage);
		PI_CloseConnection(ID);

		return 0;
	}
	else
	{
		std::cout << "All servos online" << std::endl;
		return 1;
	}


}
void stageController::moveTo(double xCoord, double yCoord, double zCoord){

	double coordArray[3];
	// move all axes the corresponding position in 'Position'
	coordArray[0] = xCoord;
	coordArray[1] = yCoord;
	coordArray[2] = zCoord;

	if ((0 <= xCoord) && (xCoord <= 200) &&
		(0 <= yCoord) && (yCoord <= 200) &&
		(0 <= zCoord) && (zCoord <= 200))
	{

		// call the MOV command (for closed servo loop).
		if (PI_MOV(ID, szAxes, coordArray))
		{
			waitUntilMoveFinished();
		}
		else
		{
			iError = PI_GetError(ID);
			PI_TranslateError(iError, szErrorMesage, 1024);
			printf("MOV: ERROR %d: %s\n", iError, szErrorMesage);
			PI_CloseConnection(ID);
		}
	}
	else
	{
		std::cout << "Out of limits" << std::endl;
	}
}
void stageController::moveTo(const double coord[3]){

	if ((0 <= coord[0]) && (coord[0] <= 200) &&
		(0 <= coord[1]) && (coord[1] <= 200) &&
		(0 <= coord[2]) && (coord[2] <= 200))
	{

		// call the MOV command (for closed servo loop).
		if (PI_MOV(ID, szAxes, coord))
		{
			waitUntilMoveFinished();
		}
		else
		{
			iError = PI_GetError(ID);
			PI_TranslateError(iError, szErrorMesage, 1024);
			printf("MOV: ERROR %d: %s\n", iError, szErrorMesage);
			PI_CloseConnection(ID);
		}
	}
	else
	{
		std::cout << "Out of limits" << std::endl;
	}
}
void stageController::move(double xDelta, double yDelta, double zDelta){

	double deltaArray[3];
	deltaArray[0] = xDelta;
	deltaArray[1] = yDelta;
	deltaArray[2] = zDelta;

	double position[3];
	getPositon(position);

	position[0] = position[0] + deltaArray[0];
	position[1] = position[1] + deltaArray[1];
	position[2] = position[2] + deltaArray[2];

	if ((0 <= position[0]) && (position[0] <= 200) &&
		(0 <= position[1]) && (position[1] <= 200) &&
		(0 <= position[2]) && (position[2] <= 200))
	{

		if (PI_MVR(ID, szAxes, deltaArray))
		{
			waitUntilMoveFinished();
		}
		else
		{
			iError = PI_GetError(ID);
			PI_TranslateError(iError, szErrorMesage, 1024);
			printf("MOV: ERROR %d: %s\n", iError, szErrorMesage);
			PI_CloseConnection(ID);
		}
	}
	else
	{
		std::cout << "Out of limits" << std::endl;
	}
}
void stageController::waitUntilMoveFinished(){
	BOOL bIsMoving[3];
	bIsMoving[0] = TRUE;
	while (bIsMoving[0] == TRUE)
	{
		////////////////////////////////////////
		// Read the moving state of the axes. //
		////////////////////////////////////////

		// if 'axes' = NULL or 'axis' is empty a general moving state of all axes ist returnd in 'bIsMoving[0]'
		// if 'bIsMoving[0]' = TRUE at least one axis of the controller ist still moving.
		// if 'bIsMoving[0]' = FALSE no axis of the contrller is moving.

		// if 'axes != NULL and 'axis' is not empty the moving state of every axis in 'axes' is returned in
		// the arry bIsMoving.
		if (!PI_IsMoving(ID, NULL /*axes = NULL*/, bIsMoving))
		{
			iError = PI_GetError(ID);
			PI_TranslateError(iError, szErrorMesage, 1024);
			printf("IsMoving: ERROR %d: %s\n", iError, szErrorMesage);
			PI_CloseConnection(ID);
		}
	}
};
void stageController::printPosition(){

	double position[3];
	if (!PI_qPOS(ID, szAxes, position))
	{
		iError = PI_GetError(ID);
		PI_TranslateError(iError, szErrorMesage, 1024);
		printf("POS?: ERROR %d: %s\n", iError, szErrorMesage);
		PI_CloseConnection(ID);
	}
	std::cout << "x : " << position[0] << "\t\t||| y : " << position[1] << "\t\t||| z : " << position[2] << std::endl;

}
void stageController::getPositon(double position[3]){

	if (!PI_qPOS(ID, szAxes, position))
	{
		iError = PI_GetError(ID);
		PI_TranslateError(iError, szErrorMesage, 1024);
		printf("POS?: ERROR %d: %s\n", iError, szErrorMesage);
		PI_CloseConnection(ID);
	}
}

//////////////////////////////////////////////////////
//					Velocity						//
//////////////////////////////////////////////////////
bool stageController::switchVelocityControlModeOn(){

	BOOL boolVCO[3];
	boolVCO[0] = 1;
	boolVCO[1] = 1;
	boolVCO[2] = 1;
	if (!PI_VCO(ID, szAxes, boolVCO))
	{
		std::cout << "ERROR occured while trying to turn on velocity control mode" << std::endl;
		return 0;
	}
	else
	{
		std::cout << "Velocity control mode ON for all channels" << std::endl;
		return 1;
	}
}
bool stageController::switchDriftControlModeOn(){

	BOOL boolDCO[3];
	boolDCO[0] = 1;
	boolDCO[1] = 1;
	boolDCO[2] = 1;
	if (!PI_DCO(ID, szAxes, boolDCO))
	{
		std::cout << "ERROR occured while trying to turn on drift control mode" << std::endl;
		return 0;
	}
	else
	{
		std::cout << "Drift control mode ON for all channels" << std::endl;
		return 1;
	}
}

void stageController::setVelocity(double xVelocity, double yVelocity, double zVelocity){

	double velocityArray[3];
	velocityArray[0] = xVelocity;
	velocityArray[1] = yVelocity;
	velocityArray[2] = zVelocity;

	PI_VEL(ID, szAxes, velocityArray);
}
void stageController::setVelocity(const double velocity[3]){

	PI_VEL(ID, szAxes, velocity);
}
void stageController::deltaVelocity(double xDeltaVelocity, double yDeltaVelocity, double zDeltaVelocity){

	//get current velocity values
	double cVelVal[3];
	getVelocity(cVelVal);

	double newVelocity[3];
	newVelocity[0] = xDeltaVelocity + cVelVal[0];
	newVelocity[1] = yDeltaVelocity + cVelVal[1];
	newVelocity[2] = zDeltaVelocity + cVelVal[2];

	if ((0 <= newVelocity[0]) && (newVelocity[0] <= 200) && (0 <= newVelocity[1]) && (newVelocity[1] <= 200) && (0 <= newVelocity[2]) && (newVelocity[2] <= 200))
	{
		setVelocity(newVelocity);
	}
	else
	{
		std::cout << "you can't go further then this" << std::endl;
	}
}

void stageController::getVelocity(double &xVelocity, double &yVelocity, double &zVelocity){

	double velocityArray[3];

	PI_qVEL(ID, szAxes, velocityArray);

	xVelocity = velocityArray[0];
	yVelocity = velocityArray[1];
	zVelocity = velocityArray[2];

}
void stageController::getVelocity(double velocity[3]){

	PI_qVEL(ID, szAxes, velocity);

}

void stageController::printVelocity(){

	double velocity[3];
	getVelocity(velocity);
	std::cout << "x-Vel : " << velocity[0] << "\t\t||| y-Vel : " << velocity[1] << "\t\t||| z-Vel : " << velocity[2] << std::endl;
}

//////////////////////////////////////////////////////
//				Trigger Digital Output				//
//////////////////////////////////////////////////////
void stageController::setLimits(int whichAxis, double min, double max){

	int piTriggerParameterArray[1];
	int piTriggerOutputIdsArray[1];
	double pdValueArray[1];
	bool tryAgain = 1;

	if (useful.qIfposibleLimitValues(min, max))
	{
		while (tryAgain == 1){

			piTriggerOutputIdsArray[0] = whichAxis;
			piTriggerParameterArray[0] = 5;
			pdValueArray[0] = min;

			tryAgain = !PI_CTO(ID, piTriggerOutputIdsArray, piTriggerParameterArray, pdValueArray, 1);
			std::cout << !tryAgain << std::endl;

			piTriggerOutputIdsArray[0] = whichAxis;
			piTriggerParameterArray[0] = 6;
			pdValueArray[0] = max;
			std::cout << PI_CTO(ID, piTriggerOutputIdsArray, piTriggerParameterArray, pdValueArray, 1) << std::endl;
		}//while
	}
	else{
		std::cout << "no valid limit values" << std::endl;
	}

}
void stageController::setTriggerMode(int whichAxis, int mode){

	int piTriggerParameterArray[1];
	int piTriggerOutputIdsArray[1];
	double pdValueArray[1];

	piTriggerOutputIdsArray[0] = whichAxis;
	piTriggerParameterArray[0] = 3;
	pdValueArray[0] = mode;
	std::cout << PI_CTO(ID, piTriggerOutputIdsArray, piTriggerParameterArray, pdValueArray, 1) << std::endl;

}
void stageController::openShutter(){
	setLimits(1, 0, 200);
}
void stageController::closeShutter(){
	setLimits(1, 0, 0);
	setLimits(2, 0, 0);
	setLimits(3, 0, 0);
}

void stageController::getLimits(int whichAxis, double &min, double &max){
	int piTriggerParameterArray[1];
	int piTriggerOutputIdsArray[1];
	double pdValueArray[1];

	piTriggerOutputIdsArray[0] = whichAxis;
	piTriggerParameterArray[0] = 5;
	PI_qCTO(ID, piTriggerOutputIdsArray, piTriggerParameterArray, pdValueArray, 1);
	min = pdValueArray[0];

	piTriggerOutputIdsArray[0] = whichAxis;
	piTriggerParameterArray[0] = 6;
	PI_qCTO(ID, piTriggerOutputIdsArray, piTriggerParameterArray, pdValueArray, 1);
	max = pdValueArray[0];
}

void stageController::getLimits(double &xMin, double &xMax, double &yMin, double &yMax, double &zMin, double &zMax){
	int piTriggerParameterArray[1];
	int piTriggerOutputIdsArray[1];
	double pdValueArray[1];

	//x Limits
	piTriggerOutputIdsArray[0] = 1;
	piTriggerParameterArray[0] = 5;
	PI_qCTO(ID, piTriggerOutputIdsArray, piTriggerParameterArray, pdValueArray, 1);
	xMin = pdValueArray[0];

	piTriggerParameterArray[0] = 6;
	PI_qCTO(ID, piTriggerOutputIdsArray, piTriggerParameterArray, pdValueArray, 1);
	xMax = pdValueArray[0];

	//y Limits
	piTriggerOutputIdsArray[0] = 2;
	piTriggerParameterArray[0] = 5;
	PI_qCTO(ID, piTriggerOutputIdsArray, piTriggerParameterArray, pdValueArray, 1);
	yMin = pdValueArray[0];

	piTriggerParameterArray[0] = 6;
	PI_qCTO(ID, piTriggerOutputIdsArray, piTriggerParameterArray, pdValueArray, 1);
	yMax = pdValueArray[0];

	//z Limits
	piTriggerOutputIdsArray[0] = 3;
	piTriggerParameterArray[0] = 5;
	PI_qCTO(ID, piTriggerOutputIdsArray, piTriggerParameterArray, pdValueArray, 1);
	zMin = pdValueArray[0];

	piTriggerParameterArray[0] = 6;
	PI_qCTO(ID, piTriggerOutputIdsArray, piTriggerParameterArray, pdValueArray, 1);
	zMax = pdValueArray[0];
}
void stageController::printLimits(){

	double xMin, xMax, yMin, yMax, zMin, zMax;
	getLimits(1, xMin, xMax);
	getLimits(2, yMin, yMax);
	getLimits(3, zMin, zMax);
	std::cout << xMin << " < x < " << xMax << std::endl << yMin << " < y < " << yMax << std::endl << zMin << " < z < " << zMax << std::endl;
}

bool stageController::checkIfAnyLimit(){
	double xMin, xMax, yMin, yMax, zMin, zMax;
	double pos[3];
	getLimits(xMin, xMax, yMin, yMax, zMin, zMax);
	getPositon(pos);
	if (((xMin <= pos[0]) && (pos[0] <= xMax)) || ((yMin <= pos[1]) && (pos[1] <= yMax)) || ((zMin <= pos[2]) && (pos[2] <= zMax)))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//////////////////////////////////////////////////////
//				Constructros						//
//////////////////////////////////////////////////////
stageController::stageController()
{
}
stageController::~stageController()
{

}
