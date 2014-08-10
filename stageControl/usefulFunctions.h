#pragma once
#include "Header.h"

using namespace std;
class usefulFunctions
{
public:
	bool cinAndCheckForDoubleAndLimits(double & xStepSize);
	bool cinAndCheckForDoubleAndLimits(double & xStepSize, double min);
	bool cinAndCheckForDoubleAndLimits(double & xStepSize, double min, double max);
	void cinAndCheckForDouble(double & xStepSize);
	bool qValueInLimits(double value);
	bool qValuesInLimits(double value1, double value2);

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

	//theta = around x axis 0<=theta<=pi
	//phi = around z axis arbitrary 
	void setRotMatrices(double rotMatX[3][3], double rotMatZ[3][3], double rotAngleX, double rotAngleZ){

		//Rotation matrix X 
		rotMatX[0][0] = 1;
		rotMatX[0][1] = 0;
		rotMatX[0][2] = 0;

		rotMatX[1][0] = 0;
		rotMatX[1][1] = cos(rotAngleX);
		rotMatX[1][2] = -sin(rotAngleX);

		rotMatX[2][0] = 0;
		rotMatX[2][1] = sin(rotAngleX);
		rotMatX[2][2] = cos(rotAngleX);

		//Rotation matrix Z 
		rotMatZ[0][0] = cos(rotAngleZ);
		rotMatZ[0][1] = -sin(rotAngleZ);
		rotMatZ[0][2] = 0;

		rotMatZ[1][0] = sin(rotAngleZ);
		rotMatZ[1][1] = cos(rotAngleX);
		rotMatZ[1][2] = 0;

		rotMatZ[2][0] = 0;
		rotMatZ[2][1] = 0;
		rotMatZ[2][2] = 1;

	}
	void matrixTimesVec(double a[3][3], double v[3]){

		double x[3];
		x[0] = 0;
		x[1] = 0;
		x[2] = 0;

		for (int i = 0; i < 3; i++){

			for (int j = 0; j < 3; j++){
				x[i] = x[i] + a[i][j] * v[j];
			}

		}
		v[0] = x[0];
		v[1] = x[1];
		v[2] = x[2];

	}

	const char * doubleToLPSTR(double x){

		const int size = 20;
		char *cs = new char[size];

		string s;
		stringstream ss;
		ss << x;
		s = ss.str();
		const char * tempAr = s.c_str();


		for (int i = 0; i < size; i++){

			cs[i] = tempAr[i];

		}

		return cs;
	}

	usefulFunctions();
	~usefulFunctions();
};

