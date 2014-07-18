#pragma once
#include "Header.h"

using namespace std;

class figures
{
private:
	
public:

	class rectangle{
	private:
		double a, b, phi0, velocity;
		
	public:
		void set(double a, double b, double phi0,double velocity);
		void cut();

		rectangle::rectangle(){}
		rectangle::~rectangle(){}
	};

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

	figures();
	~figures();
};

