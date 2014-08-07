#include "WinProc.h"

using namespace std;

char G_Text_Poly1[10] = {};

LRESULT CALLBACK WndProcNewPoly3D(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// This switch block differentiates between the message type that could have been received. If you want to
	// handle a specific type of message in your application, just define it in this block.
	switch (msg)
	{
		// This message type is used by the OS to close a window. Just closes the window using DestroyWindow(hwnd);
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
		// This message type is part of the WM_CLOSE case. After the DestroyWindow(hwnd) function is called, a 
		// WM_DESTROY message is sent to the window, which actually closes it.
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
		// This message type is an important one for GUI programming. It symbolizes an event for a button for example.
	case WM_COMMAND:
	{
					   if (wParam==ID_OK_KNOPF){
				
							GetDlgItemText(hwnd, ID_TEXT_POLY_R, &G_Text_Poly_R[0], sizeof(G_Text_Poly_R));
							GetDlgItemText(hwnd, ID_TEXT_POLY_phi0, &G_Text_Poly_phi0[0], sizeof(G_Text_Poly_phi0));
							GetDlgItemText(hwnd, ID_TEXT_POLY_velocity, &G_Text_Poly_velocity[0], sizeof(G_Text_Poly_velocity));
							GetDlgItemText(hwnd, ID_TEXT_POLY_steps, &G_Text_Poly_steps[0], sizeof(G_Text_Poly_steps));
							
					   }

						break;
	}

	default:
		// When no message type is handled in your application, return the default window procedure. In this case the message
		// will be handled elsewhere or not handled at all.
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}
