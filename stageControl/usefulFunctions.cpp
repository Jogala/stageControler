#include "usefulFunctions.h"

bool usefulFunctions::cinAndCheckForDoubleAndLimits(double & xStepSize){
	bool success = 0;
	double newValue;

	do{
		if (cin >> newValue)
		{
			if ((0 < newValue) && (newValue <= 200)){
				xStepSize = newValue;
				return 1;
			}
			else
			{
				cout << "No new value was set; value was out of range ]0,200]" << endl;
				return 0;
			}
			success = 1;
		}
		else
		{
			cout << "not a number... try again" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
	} while (!success);

}

void usefulFunctions::cinAndCheckForDouble(double & xStepSize){
	bool success = 0;
	double newValue;

	do{
		if (cin >> newValue)
		{
			
				xStepSize = newValue;
				success = 1;
		}
		else
		{
			cout << "not a number... try again" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
	} while (!success);
}
	
bool usefulFunctions::qValueInLimits(double value){
	if ((0 <= value) && (value <= 200)){
		return 1;
	}
	else{
		return 0;
	}
}

bool usefulFunctions::qValuesInLimits(double value1,double value2){
	if ((0 <= value1) && (value1 <= 200) && (0 <= value2) && (value2 <= 200)){
		return 1;
	}
	else{
		return 0;
	}
}

bool usefulFunctions::qIfposibleLimitValues(double min, double max){
	if ((0 <= min) && (min <= 200) && (0 <= max) && (max <= 200)){
		if (min <= max){
			return 1;
		}
		else{
			return 0;
		}
	}
	else{
		return 0;
	}
}

usefulFunctions::usefulFunctions()
{
}


usefulFunctions::~usefulFunctions()
{
}
