
// Include the defaut Win32 header, you need functions from it
#include "Header.h"
#include "./PI_stuff/PI_GCS2_DLL.h" 
#include "moveStageUsingKeyboard.h"
#include "figures.h"
#include "figuresWriteCoordToFile.h"
#include "menu.h"
#include "WinProc.h"

using namespace std;


// Declare a HWND (Window Handle) for every control you want to use in your application.
// In this tutorial, a button and a text field are used. The window itself also has a window handle.



int main(int argc, char* argv[])
{

	//stageController E545;
	//menu menu(E545);

	//E545.initialize();
	//menu.mainMenu();

	//E545.closeConnection();

	figuresWriteCoordToFile::polygon poly;
	poly.regMenuWindow();

	poly.openWindowSet3D();
	Sleep(200);
	poly.openWindowSet3D();
	

}






