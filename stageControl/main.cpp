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
#include "moveStageUsingArrows.h"
using namespace std;

bool checkForDouble(std::string const& s, double &d) {
	istringstream ss(s);
	return (ss >> d) && (ss >> ws).eof() == 1;
}

int main(int argc, char* argv[])
{
	//Initialization
	stageControler E545;
	E545.printNameOfConnectedAxis();
	E545.establishConnection();
	E545.printNameOfConnectedAxis();
	E545.switchChannelsOn();
	E545.switchAllServosOn();
	E545.switchVelocityControlModeOn();
	E545.switchDriftControlModeOn();
	E545.setVelocity(50, 50, 50);
	E545.moveTo(100, 100, 100);

	E545.setVelocity(10, 10, 10);
	//cut cut(E545);
	//cut.rectangle(20, 20);



	E545.minMaxTrigger(1, 90, 100);
	//E545.minMaxTrigger(2, 90, 95);
	bool EXIT=0;
	double xVelocity;
	double yVelocity;
	string userIn;
	while (!EXIT){
		moveStageUsingArrows(E545);
		cout << "xVelocity or exit with something else" << endl;
		cout << "xVelocity = ";
		cin >> userIn;
		if (checkForDouble(userIn,xVelocity)){
			cout << "yVelocity = ";
			cin >> userIn;
			if (checkForDouble(userIn, yVelocity)){
				E545.setVelocity(xVelocity, yVelocity, 10);
			}
			else
			{
				EXIT = 1;
			}
		}
		else{
			EXIT = 1;
		}
	}




	E545.closeConnection();
	return 0;
}


