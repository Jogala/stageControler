#include "stageControler.h"


void stageControler::establishConnection(){
	ID = PI_ConnectRS232(1, 115200);
	if (ID<0)
	{
		iError = PI_GetError(ID);
		PI_TranslateError(iError, szErrorMesage, 1024);
		printf("ConnectRS232: ERROR %d: %s\n", iError, szErrorMesage);
	}
}

void stageControler::closeConnection(){
	
		PI_CloseConnection(ID);
		std::cout << "Connection closed" <<std::endl;
}

void stageControler::printNameOfConnectedAxis(){

	if (!PI_qSAI(ID, szAxes, 16))
	{
		iError = PI_GetError(ID);
		PI_TranslateError(iError, szErrorMesage, 1024);
		printf("SAI?: ERROR %d: %s\n", iError, szErrorMesage);
		PI_CloseConnection(ID);
	}
	printf(">SAI?:\n%s\n", szAxes);
}

void stageControler::switchChannelsOn(){
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
	}
	printf(">ONL 1 1 2 1 3 1\n\n");
}

void stageControler::switchAllServosOn(){

	// Switch on the Servo for all axes
	servosStatus[0] = TRUE; // servo on for first axis in the string 'axes'.
	servosStatus[1] = TRUE; // servo on for second axis in the string 'axes'.
	servosStatus[2] = TRUE; // servo on for third axis in the string 'axes'.

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

void stageControler::moveTo(double xCoord, double yCoord, double zCoord){
	
	double coordArray[3];
	// move all axes the corresponding position in 'Position'
	coordArray[0] = xCoord; 
	coordArray[1] = yCoord; 
	coordArray[2] = zCoord; 

	// call the MOV command (for closed servo loop).
	if(!PI_MOV(ID, szAxes, coordArray))
	{
		iError = PI_GetError(ID);
		PI_TranslateError(iError, szErrorMesage, 1024);
		printf("MOV: ERROR %d: %s\n", iError, szErrorMesage);
		PI_CloseConnection(ID);
	}
	printf(">MOV 1 2.0 2 1.0 3 0.5\n\n");
}

void stageControler::moveTo(double coordArray[3]){

	// call the MOV command (for closed servo loop).
	if (!PI_MOV(ID, szAxes, coordArray))
	{
		iError = PI_GetError(ID);
		PI_TranslateError(iError, szErrorMesage, 1024);
		printf("MOV: ERROR %d: %s\n", iError, szErrorMesage);
		PI_CloseConnection(ID);
	}
	printf(">MOV 1 2.0 2 1.0 3 0.5\n\n");
}





stageControler::stageControler()
{
}


stageControler::~stageControler()
{
}
