#pragma once
#include "Header.h"
#include "stageController.h"
#include "usefulFunctions.h"

using namespace std;

class figuresWriteCoordToFile
{
private:


public:
	//////////////////////////////
	//		rectangle			//
	//////////////////////////////
	class rectangle{
	private:
		double a, b, phi0, velocity;

	public:
		void set(double a, double b, double phi0, double velocity);
		void cut();

		rectangle::rectangle(){}
		rectangle::~rectangle(){}
	};

	//////////////////////////////////////
	//		surface rectangle			//
	//////////////////////////////////////
	class surfaceRectangle{
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
	class polygon{
	private:
		double R, phi0, velocity;
		int steps;

	public:
		void set(double R, double phi0, int steps, double velocity);
		void cut();

		polygon::polygon(){}
		polygon::~polygon(){}
	};

	figuresWriteCoordToFile();
	~figuresWriteCoordToFile();
};

