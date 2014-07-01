#include "rectangle.h"


rectangle::rectangle(double inX, double inY, double inVel)
{
	itsX = inX;
	itsY = inY;
	itsVel = inVel;

	//Delay times have to be multiplied by 1000 in order to convert them from s to ms
	double xDelay = 1000.0 * (inX / inVel);
	double yDelay = 1000.0 * (inY / inVel);		  
	double hdiagDelay = 1000.0 *(0.5* sqrt((inX)*(inX) + (inY)*(inY))/inVel);

	fstream recFstream;
	stringstream recSstream;

	recSstream << "rectangle" << ".txt";
	recFstream.open(recSstream.str(), fstream::out | fstream::trunc);
	//trunc::truncate::Any contents that existed in the file before it is open are discarded.
	//Start writing into text file

	recFstream << "MAC BEG rectangle" << endl;
	recFstream << "VEL A " << inVel << " B " << inVel << " C " << 0 << endl;
	recFstream << "MVR A " << -0.5*inX << " B " << 0.5*inY << " C " << 0 << endl;
	recFstream << "DEL " << hdiagDelay << endl;
	//TURN LASER ON
	recFstream << "MVR A " << inX << " B " << 0 << " C " << 0 << endl;
	recFstream << "DEL " << xDelay << endl;
	recFstream << "MVR A " << 0 << " B " << -inY << " C " << 0 << endl;
	recFstream << "DEL " << yDelay << endl;
	recFstream << "MVR A " << -inX << " B " << 0 << " C " << 0 << endl;
	recFstream << "DEL " << xDelay << endl;
	recFstream << "MVR A " << 0 << " B " << +inY << " C " << 0 << endl;
	recFstream << "DEL " << yDelay << endl;
	//TURN LASER OFF
	recFstream << "MVR A " << 0.5*inX << " B " << -0.5*inY << " C " << 0 << endl;
	recFstream << "DEL " << hdiagDelay << endl;
	recFstream << "MAC END" << endl;

	//End writing into text file
	recFstream.close();

}
