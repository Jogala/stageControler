#pragma once
#include "Header.h"
#include "stageController.h"
#include "usefulFunctions.h"

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
	//		rectangle			//
	//////////////////////////////
	class rectangle : public figures
	{
	private:
		stageController * pointerToE545;
		double a, b, phi0, velocity;
	
		//leaveOrSwap leaves a and b unchanged if -45<=phi<=45 or 135<=phi<=225
		//and adjusts phi
		void leaveOrSwapAndAdjustPhi(double &phi, double &a, double &b);

	public:
		void set(double a, double b, double phi0, double velocity);
		void cutRel();
		void cutAbs();
		void cutAbsLim();

		rectangle(stageController &E545){

			pointerToE545 = &E545;
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
		double xRotMat[3][3];
		double zRotMat[3][3];

	public:
		void set(double R, double phi0, int steps, double velocity);
		void cutRel();
		void cutAbs();
		void cutAbs3D();
		void set3D(double RIn, double phi0In, double rotAngleXIn, double rotAngleZIn, int stepsIn, double velocityIn);
		polygon(stageController &E545){

			pointerToE545 = &E545;
		}
		~polygon(){}

	};

}