#pragma once
#include "Header.h"
#include "usefulFunctions.h"
#include "stageController.h"
#include "figures.h"

using namespace std;

class menu
{


private: 
	
	usefulFunctions useful;
	stageController * pToE545;

	//Werden im constructor initzialisiert 
	figures::line line;
	figures::rectangle rectangle;
	figures::surfaceRectangle surfaceRectangle;
	figures::polygon polygon;
	figures::spiral spiral;

	double stepSize[3];
	double velStepSize[3];
	double shutterOpenTime;
	double minShutterClosedTime;
	double sleepValue;

	void printMenu();
	void settingsMenu();

	void cutMainMenu();
	void cutNewFigureMenu();
	void cutCutMenu();

	void openShutterMenu();
	void openShutterPulsedMenu();

	void moveUsingArrowsMenu(const bool windowActive);
	void controlVelocitiesMenu(const bool windowActive);
	void setLimitsMenu();
	void helpMenu();
	void moveToMenu();
	
public:
	
	void mainMenu();

	menu::menu(stageController & E545)
	{
		pToE545 = &E545;

		//This has to be done because C++ is stupid 
		//http://stackoverflow.com/questions/9802341/constructor-and-initialization-of-custom-classes-objects
		//This is the reason why we needed the default constructors for the different figures
		figures::line newLine(E545);
		line = newLine;

		figures::rectangle newRectangle(E545);
		rectangle = newRectangle;

		figures::surfaceRectangle newSurfaceRectangle(E545);
		surfaceRectangle = newSurfaceRectangle;

		figures::polygon newPolygon(E545);
		polygon = newPolygon;

		figures::spiral newSpiral(E545);
		spiral = newSpiral;

		stepSize[0] = 1;
		stepSize[1] = 1;
		stepSize[2] = 1;

		velStepSize[0] = 1;
		velStepSize[1] = 1;
		velStepSize[2] = 1;
		
		shutterOpenTime=100;
		minShutterClosedTime=100;
		sleepValue=50;

		line.loadValuesFromTextFile();
		rectangle.loadValuesFromTextFile();
		polygon.loadValuesFromTextFile();
		spiral.loadValuesFromTextFile();

		rectangle.regMenuWindow();
		polygon.regMenuWindow();
		line.regMenuWindow();
		spiral.regMenuWindow();

	}


	menu::~menu()
	{
	}
};

