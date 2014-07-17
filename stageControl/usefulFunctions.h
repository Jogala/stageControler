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
			
	usefulFunctions();
	~usefulFunctions();
};

