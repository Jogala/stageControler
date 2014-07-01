#include <string>
#include <iostream>
#include "rectangle.h"

using namespace std;

class menu
{
public:
	double xDim, yDim, zDim, velocity;
	string userChoice;

	void DisplayMainMenuAndReturnChoice();
	void nr();
	menu();
};

