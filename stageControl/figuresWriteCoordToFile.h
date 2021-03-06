#pragma once
#include "Header.h"
#include "stageController.h"
#include "usefulFunctions.h"
#include "WinProc.h"

using namespace std;

namespace figuresWriteCoordToFile{

	class figuresWriteCoordToFile
	{
	private:

	protected:
		usefulFunctions use;
		figuresWriteCoordToFile(){}
		~figuresWriteCoordToFile(){}

	};

	//////////////////////////////
	//		line				//
	//////////////////////////////
	class line : public figuresWriteCoordToFile
	{
	private:
		double l, phi,theta, velocity;
		int repetitions;
		double xRotMat[3][3];
		double zRotMat[3][3];

		//leaveOrSwap leaves a and b unchanged if -45<=phi<=45 or 135<=phi<=225
		//and adjusts phi

	public:
		void set3D(double lIn, double phiIn, double thetaIn, double  velocityIn, int repetionsIn);
		void cutRel3D();
		void cutAbs3D();

		line(){
		}

	};

	//////////////////////////////
	//		rectangle			//
	//////////////////////////////
	class rectangle : public figuresWriteCoordToFile{
	private:
		double a, b, phi0, velocity;

	public:
		void set(double a, double b, double phi0, double velocity);
		void leaveOrSwapAdjustPhi(double &phi, double &a, double &b);
		void cut();
		void cutAbsLim();

		rectangle::rectangle(){
		}
		rectangle::~rectangle(){}
	};

	//////////////////////////////////////
	//		surface rectangle			//
	//////////////////////////////////////
	class surfaceRectangle : public figuresWriteCoordToFile{
	private:
		double a, b, phi0, velocity;
		int resolution;
		char orientation;

	public:
		void set(double aIn, double bIn, double phi0In, double velocityIn, int resoluationIn, char longOrShortSide);
		void cut();

		surfaceRectangle::surfaceRectangle(){}
		surfaceRectangle::~surfaceRectangle(){}
	};


	//////////////////////////////
	//			polygon			//
	//////////////////////////////
	class polygon : public figuresWriteCoordToFile{
	private:
		
		double R, phi0, velocity;
		int steps;
		double rotAngleX, rotAngleZ;
		double xRotMat[3][3];
		double zRotMat[3][3];

		//get called by constructor, should only be opend once. 
		bool regMenuWindow();

	public:
		void set(double RIn, double phi0In, int stepsIn, double velocityIn);
		void cut();
		void set3D(double RIn, double phi0In, double rotAngleXIn, double rotAngleZIn, int stepsIn, double velocityIn);
		void cutAbs3D();

		//set Values using Window
		void openWindowSet3D();

		polygon::polygon(){
			regMenuWindow();
		}
		polygon::~polygon(){}
	};

}


