#pragma once
#include "Header.h"

using namespace std;
class usefulFunctions
{
public:

	bool cinAndCheckForDoubleAndLimits(double & xStepSize);
	void cinAndCheckForDouble(double & xStepSize);
	bool qValueInLimits(double value);
	bool qValuesInLimits(double value1, double value2);
	bool qIfposibleLimitValues(double min, double max);

	void radToDegByRef(double &phi){

		phi = (phi / (2 * pi)) * 360;

	}
	void degToRadByRef(double &phi){
		phi = (phi / 360) * (2 * pi);
	}
	double radToDegByValue(double phi){

		phi = (phi / (2 * pi)) * 360;

		return phi;
	}
	double degToRadByValue(double phi){
		phi = (phi / 360) * (2 * pi);
		return phi;
	}

			
	usefulFunctions();
	~usefulFunctions();
};

