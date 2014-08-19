//Version 8.8.2014 10:23
// Include the defaut Win32 header, you need functions from it
#include "Header.h"
#include "./PI_stuff/PI_GCS2_DLL.h" 
#include "figures.h"
#include "menu.h"
#include "WinProc.h"
#include <Eigen/Core>

using namespace std;


// Declare a HWND (Window Handle) for every control you want to use in your application.
// In this tutorial, a button and a text field are used. The window itself also has a window handle.



int main(int argc, char* argv[])
{

	stageController E545;
	menu menu(E545);
	
	E545.initialize();
	
	menu.mainMenu();

	E545.closeConnection();	

	//figures::spiral spiral(E545);

	//while (1){
	//	spiral.regMenuWindow();
	//	spiral.openWindowSet3D();
	//	spiral.cutAbsMacroSpiral3D();
	//}

	

}






