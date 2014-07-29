#pragma once
#include "Header.h"
#include "stageController.h"
#include "usefulFunctions.h"

using namespace std;
//This maybe seems confusing... I declared a namespace "figuresWriteCoordToFile"
//here because I ant to use for example "figuresWriteCoordToFile::rectangle rec" and 
//"figures::rectangle myRec"
//Something like "figuresWriteCoordToFile::figuresWriteCoordToFile myFigure" can not 
//occure becaue the contructors of "figuresWriteCoordToFile" are set to protected. 
//the same is true for the class and namespace figures. 
//This has the advantage that I can give all child classes shared functions or objects
//(like usefulFunctions) by writing them into the parent class, and I can still use namespace.
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
		double xRotMat[3][3];
		double zRotMat[3][3];

	public:
		void set(double RIn, double phi0In, int stepsIn, double velocityIn);
		void cut();
		void set3D(double RIn, double phi0In, double rotAngleX, double rotAngleZ, int stepsIn, double velocityIn);
		void cutAbs3D();

		polygon::polygon(){}
		polygon::~polygon(){}
	};

}


