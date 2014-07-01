#include "menu.h"

void menu::DisplayMainMenuAndReturnChoice()
{
	cout << "Welcome to macroCreater for E-545" << endl;
	cout << "Choose one of the following options"<<endl;
	cout << endl;
	cout << "[r]\t rectangle using saved parameters" << endl;
	cout << "[nr]\t new rectangle" << endl;
	cout << "[s]\t square using saved parameters" << endl;
	cout << "[ns]\t new square" << endl;
	cout << "[c]\t circle using saved parameters" << endl;
	cout << "[nc]\t new circle" << endl;
	cout << endl;
	cout << "or type \"exit\""<< endl;
	cin >>  userChoice;

	if (userChoice=="exit")
	{

	}
	else
	{
		if (userChoice == "r")
		{
			rectangle myRectangle(100, 100, 100);
		}
		else
		{
			if (userChoice == "nr")
			{	
				nr();
			}
			else
			{
				cout << "Option not avaliable" << endl;
			}

		}
		
	}
}

void menu::nr()
{
	cout << "Enter Parameters for new rectangle" << endl;
	cout << "x = ";
	cin >> xDim;
	cout << "y = ";
	cin >> yDim;
	cout << "velocity = ";
	cin >> velocity;

	rectangle myRectangle(xDim, yDim, velocity);

}

menu::menu()
{
}
