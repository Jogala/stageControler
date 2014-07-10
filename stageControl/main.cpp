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
#include "moveStageUsingKeyboard.h"
using namespace std;

bool checkForDouble(std::string const& s, double &d) {
	istringstream ss(s);
	return (ss >> d) && (ss >> ws).eof() == 1;
}

int main(int argc, char* argv[])
{



	//Initialization
	stageController E545;
	E545.initialize();

	//E545.setVelocity(40, 40, 40);

	//string whatEver;
	//cout << "for cut enter what ever" << endl;
	//cin >> whatEver;
	cut cut(E545);
	cut.rectangle(20, 20);
	//cout << "for leaving enter what ever" << endl;
	//cin >> whatEver;
	
	E545.closeConnection();
	return 0;
}


