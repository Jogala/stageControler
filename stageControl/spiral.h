#pragma once
#include "figures.h"

namespace figures{
	//////////////////////////////
	//			spiral			//
	//////////////////////////////
	class spiral : public figures{
	private:
		stageController * pointerToE545;
		double itsR, phi0, velocity;
		int steps;
		double rotAngleX, rotAngleZ;
		int sectors;
		double radiusRatio;

	public:
		bool regMenuWindow();
		void loadValuesFromTextFile();
		void cutAbsMacroSpiral3D();
		void printMemberVariables(){

			cout << "itsR = " << "\t" << itsR << endl;
			cout << "phi0 = " << "\t" << phi0 << endl;
			cout << "xRot = " << "\t" << rotAngleX << endl;
			cout << "zRot = " << "\t" << rotAngleZ << endl;
			cout << "steps = " << "\t" << steps<< endl;
			cout << "sectors = " << "\t" << sectors<< endl;
			cout << "radiusRatio = " << "\t" << radiusRatio << endl;
			cout << "velocity = " << "\t" << rotAngleZ << endl;

		}

		void set3D(double RIn, double phi0In, double rotAngleXIn, double rotAngleZIn, int stepsIn, double velocityIn);

		//set Values using Window
		void openWindowSet3D();


		//void cutCircleViaMacro();

		spiral(stageController &E545){
			pointerToE545 = &E545;
		}
		spiral(){


		}

		~spiral(){

		}

	};
}