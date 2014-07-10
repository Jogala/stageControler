#include "stageController.h"

void stageController::initialize(){
	establishConnection();
	printNameOfConnectedAxis();
	switchChannelsOn();
	switchAllServosOn();
	switchVelocityControlModeOn();
	switchDriftControlModeOn();	

	setVelocity(50, 50, 50);
	moveTo(100, 100, 100);
	minMaxTrigger000();
	moveTo(100, 100, 100);
	
}
void stageController::establishConnection(){
	ID = PI_ConnectRS232(1, 115200);
	std::cout << "ID = " << ID << std::endl;
	if (ID < 0)
	{
		iError = PI_GetError(ID);
		PI_TranslateError(iError, szErrorMesage, 1024);
		printf("ConnectRS232: ERROR %d: %s\n", iError, szErrorMesage);
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
	printf(">SAI?:\n%s\n", szAxes);
}
void stageController::switchChannelsOn(){
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
	}
	printf(">ONL 1 1 2 1 3 1\n\n");
}

//////////////////////////////////////////////////////
//					Move							//
//////////////////////////////////////////////////////
void stageController::switchAllServosOn(){

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
	}
	printf(">SVO A 1 B C 3 1\n\n");

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
void stageController::switchVelocityControlModeOn(){

	BOOL boolVCO[3];
	boolVCO[0] = 1;
	boolVCO[1] = 1;
	boolVCO[2] = 1;
	PI_VCO(ID, szAxes, boolVCO);
}
void stageController::switchDriftControlModeOn(){

	BOOL boolDCO[3];
	boolDCO[0] = 1;
	boolDCO[1] = 1;
	boolDCO[2] = 1;
	PI_DCO(ID, szAxes, boolDCO);
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

	if ((0 <= newVelocity[0] <= 200) && (0 <= newVelocity[1] <= 200) && (0 <= newVelocity[2] <= 200))
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
void stageController::minMaxTrigger(int whichAxis, double minimum, double maximum){

	int piTriggerParameterArray[1];
	int piTriggerOutputIdsArray[3];
	double pdValueArray[1];

	bool tryAgain = 1;
	while (tryAgain == 1){

		piTriggerOutputIdsArray[0] = whichAxis;
		piTriggerParameterArray[0] = 3;
		pdValueArray[0] = 3;
		std::cout << PI_CTO(ID, piTriggerOutputIdsArray, piTriggerParameterArray, pdValueArray, 1) << std::endl;

		piTriggerOutputIdsArray[0] = whichAxis;
		piTriggerParameterArray[0] = 5;
		pdValueArray[0] = minimum;


		tryAgain = !PI_CTO(ID, piTriggerOutputIdsArray, piTriggerParameterArray, pdValueArray, 1);
		std::cout << !tryAgain << std::endl;



		piTriggerOutputIdsArray[0] = whichAxis;
		piTriggerParameterArray[0] = 6;
		pdValueArray[0] = maximum;
		std::cout << PI_CTO(ID, piTriggerOutputIdsArray, piTriggerParameterArray, pdValueArray, 1) << std::endl;
	}

}
void stageController::minMaxTrigger000(){
	minMaxTrigger(1, 0, 1);
	minMaxTrigger(2, 0, 1);
	minMaxTrigger(3, 0, 1);
}

//////////////////////////////////////////////////////
//				Constructros						//
//////////////////////////////////////////////////////
stageController::stageController()
{
}
stageController::~stageController()
{
	//minMaxTrigger000();
	//setVelocity(50, 50, 50);
	//moveTo(100, 100, 100);
	//closeConnection();
}
