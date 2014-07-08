//E545.setVelocity(2, 2, 1);
//cut cut(E545);
//cut.rectangle(20,20);







//E545.minMaxTrigger(2, 50, 80);
//E545.setVelocity(100, 100, 100);
//E545.moveTo(0, 0, 0);
////double xVelocity;
//while (!(GetKeyState(0x51) & 0x8000) && !(GetKeyState(VK_ESCAPE) & 0x8000))
//{
//	cout << "Velocity it will go to 200?" << endl;
//	cin >> xVelocity;
//	E545.setVelocity(100, xVelocity, 100);
//	E545.moveTo(0, 30, 0);
//	cout << "Velocity it will go to 0?" << endl;
//	cin >> xVelocity;
//	E545.setVelocity(100, xVelocity, 100);
//	E545.moveTo(0, 110, 0);
//}



////Steuereinheit 
//while (!(GetKeyState(0x51) & 0x8000) && !(GetKeyState(VK_ESCAPE) & 0x8000)){
//	//left
//	while ((GetKeyState(0x25) & 0x8000))
//	{
//		E545.move(-1.0*xStepSize, 0, 0);
//		Sleep(100);
//	}
//
//	//right
//	while ((GetKeyState(0x27) & 0x8000))
//	{
//		E545.move(1.0*xStepSize, 0, 0);
//		Sleep(100);
//	}
//
//	//down
//	while ((GetKeyState(0x28) & 0x8000))
//	{
//		E545.move(0, -1.0*yStepSize, 0);
//		Sleep(100);
//	}
//
//	//up
//	while ((GetKeyState(0x26) & 0x8000))
//	{
//		E545.move(0, 1.0*yStepSize, 0);
//		Sleep(100);
//	}
//
//}





//double xVel;
//double yVel;
//string myString;
//cout << "Set xVelocity and yVelocity or  for exit" << endl;
//cout << "xVel = ";
//cin >> myString;
//
//if (checkForDouble(myString, xVel) == 1){
//	cout << "yVel = ";
//	cin >> myString;
//	if (checkForDouble(myString, yVel) == 1){
//		E545.setVelocity(xVel, yVel, 10);
//	}
//	else{
//		if (checkForDouble(myString, xVel) == 0){
//			EXIT = 1;
//		}
//	}
//}
//else{
//	if (checkForDouble(myString, xVel) == 0){
//		EXIT = 1;
//	}
//	else{
//
//	}
//}






	////E545.minMaxTrigger(1, 90, 100);
	//E545.minMaxTrigger(2, 90, 100);
	//bool EXIT=0;
	//double xVelocity;
	//double yVelocity;
	//string userIn;
	//while (!EXIT){
	//	moveStageUsingArrows(E545);
	//	cout << "xVelocity or exit with something else" << endl;
	//	cout << "xVelocity = ";
	//	cin >> userIn;
	//	if (checkForDouble(userIn,xVelocity)){
	//		cout << "yVelocity = ";
	//		cin >> userIn;
	//		if (checkForDouble(userIn, yVelocity)){
	//			E545.setVelocity(xVelocity, yVelocity, 10);
	//		}
	//		else
	//		{
	//			EXIT = 1;
	//		}
	//	}
	//	else{
	//		EXIT = 1;
	//	}
	//}