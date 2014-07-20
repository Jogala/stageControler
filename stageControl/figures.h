#pragma once
#include "Header.h"
#include "stageController.h"
#include "usefulFunctions.h"


namespace figures{

	//////////////////////////////
	//		rectangle			//
	//////////////////////////////
	class rectangle
	{
	private:
		stageController * pointerToE545;
		double a, b, phi0, velocity;

		//leaveOrSwap leaves a and b unchanged if -45<=phi<=45 or 135<=phi<=225
		void leaveOrSwap(double &phi, double &a, double &b);

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
	class surfaceRectangle 
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
	class polygon{
	private:
		stageController * pointerToE545;
		double R, phi0, velocity;
		int steps;

	public:
		void set(double R, double phi0, int steps, double velocity);
		void cutRel();
		void cutAbs();

		polygon(stageController &E545){

			pointerToE545 = &E545;
		}
		~polygon(){}

	};

}