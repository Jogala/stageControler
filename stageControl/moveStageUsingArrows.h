#pragma once
#include "Header.h"
#include "stageControler.h"

using namespace std;


void moveStageUsingArrows(stageControler &E545){

	double xStepSize = 0.5;
	double yStepSize = 0.5;

	bool EXIT = 0;
	while (!EXIT){

		while (!(GetKeyState(0x51) & 0x8000) && !(GetKeyState(VK_ESCAPE) & 0x8000)){
			//left
			while ((GetKeyState(0x25) & 0x8000))
			{
				E545.move(-1.0*xStepSize, 0, 0);
				Sleep(100);
			}

			//right
			while ((GetKeyState(0x27) & 0x8000))
			{
				E545.move(1.0*xStepSize, 0, 0);
				Sleep(100);
			}

			//down
			while ((GetKeyState(0x28) & 0x8000))
			{
				E545.move(0, -1.0*yStepSize, 0);
				Sleep(100);
			}

			//up
			while ((GetKeyState(0x26) & 0x8000))
			{
				E545.move(0, 1.0*yStepSize, 0);
				Sleep(100);
			}

			EXIT = 1;

		}
	}

}