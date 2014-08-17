#pragma once
#include "Header.h"
#include "stageController.h"
#include "usefulFunctions.h"
#include "WinProc.h"
#include <Eigen/Core>

//This maybe seems confusing... I declared a namespace "figuresWriteCoordToFile"
//here because I ant to use for example "figuresWriteCoordToFile::rectangle rec" and 
//"figures::rectangle myRec"
//Something like "figuresWriteCoordToFile::figuresWriteCoordToFile myFigure" can not 
//occure becaue the contructors of "figuresWriteCoordToFile" are set to protected. 
//the same is true for the class and namespace figures. 
//This has the advantage that I can give all child classes shared functions or objects
//(like usefulFunctions) by writing them into the parent class, and I can still use namespace.
namespace figures{

	class figures
	{
	private:

	protected:
		usefulFunctions use;
		figures(){}
		~figures(){}
	};

	//////////////////////////////
	//		line				//
	//////////////////////////////
	class line : public figures
	{
	private:
		stageController * pointerToE545;
		double l, phi, velocity, theta;
		int repetitions;
		string nameFile = "lineLastValues.txt";

		//leaveOrSwap leaves a and b unchanged if -45<=phi<=45 or 135<=phi<=225
		//and adjusts phi

	public:
		void printMemberValues(){
		
			cout << "l" << "\t\t\t" << l << endl;
			cout << "phi" << "\t\t\t" << (phi/(2*pi))*360 << endl;
			cout << "theta" << "\t\t\t" << (theta / (2 * pi)) * 360 << endl;
			cout << "repetitions" << "\t\t" << repetitions << endl;
			cout << "velocity" << "\t\t" << velocity << endl;

		}
		void loadValuesFromTextFile();
		void writeVariablesToTextFile(double l, double phi, double theta, int repetitions, double velocity);

		void set3D(double lIn, double phi0In, double thetaIn, double velocityIn, int repetionsIn);
		void cutRel3D();
		void cutAbs3D();
		void cutAbsLim3D();
	

		bool regMenuWindow();
		void openWindowSet3D();

		void set(double l, double phi0, double velocity, int repetitions);
		void cutRel();
		void cutAbs();

		line(stageController &E545){
		
			pointerToE545 = &E545;

		}
		//Default constructor is needed! Because I am using line as a member of a class see 
		//http://stackoverflow.com/questions/9802341/constructor-and-initialization-of-custom-classes-objects
		line(){

		}
		~line(){}

	};



	//////////////////////////////
	//		rectangle			//
	//////////////////////////////
	class rectangle : public figures
	{
	private:
		stageController * pointerToE545;
		double a, b, velocity;
		double rotAngleX, rotAngleZ, phi0;

		//leaveOrSwap leaves a and b unchanged if -45<=phi<=45 or 135<=phi<=225
		//and adjusts phi
		void leaveOrSwapAndAdjustPhi(double &phi, double &a, double &b);

	public:
		void set(double a, double b, double rotAngleZ, double velocity);
		void cutRel();
		void cutAbs();
		void cutAbsLim2D();
		void cutAbs3D();

		void macroAbs3D();
		void startMacroAbs3D();

		void openWindowSet3D();
		bool regMenuWindow();
		void loadValuesFromTextFile();

		void printMemberVariables();

		rectangle(stageController &E545){

			pointerToE545 = &E545;
		}
		
		rectangle(){		
		}
		~rectangle(){}

	};


	//////////////////////////////////////
	//		surface rectangle			//
	//////////////////////////////////////
	class surfaceRectangle : public figures
	{
	private:
		stageController * pointerToE545;
		double a, b, phi0, velocity;
		int resolution;
		char orientation;

	public:
		void set(double aIn, double bIn, double phi0In, double velocityIn, int resoluationIn, char longOrShortSide);
		void cutRel();
		void cutAbs();

		surfaceRectangle(stageController &E545){

			pointerToE545 = &E545;
		}

		surfaceRectangle(){	
		}

		~surfaceRectangle(){}

	};

	//////////////////////////////
	//			polygon			//
	//////////////////////////////
	class polygon : public figures{
	private:
		stageController * pointerToE545;
		double R, phi0,velocity;
		int steps;
		double rotAngleX, rotAngleZ;
		string circleMacroName = "macroCircle";
		
	
	public:
		double delayFactor = 1;
		bool regMenuWindow();
		void loadValuesFromTextFile();
		void set(double R, double phi0, int steps, double velocity);
		void cutRel();
		void cutAbs();
		void cutAbs3D();
		void set3D(double RIn, double phi0In, double rotAngleXIn, double rotAngleZIn, int stepsIn, double velocityIn);
	
		//set Values using Window
		void openWindowSet3D();
		
		void cutCircleViaMacro();

		polygon(stageController &E545){
			pointerToE545 = &E545;
		}
		polygon(){
			

		}

		~polygon(){

		}

	};

}