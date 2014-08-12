#include "WinProc.h"

using namespace std;



//polygon
BOOL poly_BOOL = 0;
char G_Text_Poly_R[4] = {};
char G_Text_Poly_phi0[4] = {};
char G_Text_Poly_velocity[5] = {};
char G_Text_Poly_steps[5] = {};
char G_Text_Poly_xRotWinkel[5] = {};
char G_Text_Poly_zRotWinkel[5] = {};

LRESULT CALLBACK WndProcNewPoly3D(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// This switch block differentiates between the message type that could have been received. If you want to
	// handle a specific type of message in your application, just define it in this block.
	switch (msg)
	{

	case DM_GETDEFID: break;
	case DM_SETDEFID: break;
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
			switch (wParam){

			case ID_OK_KNOPF_POLY:
				{

					GetDlgItemText(hwnd, ID_TEXT_POLY_R, &G_Text_Poly_R[0], sizeof(G_Text_Poly_R));
					GetDlgItemText(hwnd, ID_TEXT_POLY_phi0, &G_Text_Poly_phi0[0], sizeof(G_Text_Poly_phi0));
					GetDlgItemText(hwnd, ID_TEXT_POLY_velocity, &G_Text_Poly_velocity[0], sizeof(G_Text_Poly_velocity));
					GetDlgItemText(hwnd, ID_TEXT_POLY_steps, &G_Text_Poly_steps[0], sizeof(G_Text_Poly_steps));
					GetDlgItemText(hwnd, ID_TEXT_POLY_xRotWinkel, &G_Text_Poly_xRotWinkel[0], sizeof(G_Text_Poly_xRotWinkel));
					GetDlgItemText(hwnd, ID_TEXT_POLY_zRotWinkel, &G_Text_Poly_zRotWinkel[0], sizeof(G_Text_Poly_zRotWinkel));
					poly_BOOL = 1;
					DestroyWindow(hwnd);
				}
				break;

			case IDOK:
				{

					//If Enter key and Button in focus
					if ((GetDlgCtrlID(GetFocus()) == ID_OK_KNOPF_POLY)){
						GetDlgItemText(hwnd, ID_TEXT_POLY_R, &G_Text_Poly_R[0], sizeof(G_Text_Poly_R));
						GetDlgItemText(hwnd, ID_TEXT_POLY_phi0, &G_Text_Poly_phi0[0], sizeof(G_Text_Poly_phi0));
						GetDlgItemText(hwnd, ID_TEXT_POLY_velocity, &G_Text_Poly_velocity[0], sizeof(G_Text_Poly_velocity));
						GetDlgItemText(hwnd, ID_TEXT_POLY_steps, &G_Text_Poly_steps[0], sizeof(G_Text_Poly_steps));
						GetDlgItemText(hwnd, ID_TEXT_POLY_xRotWinkel, &G_Text_Poly_xRotWinkel[0], sizeof(G_Text_Poly_xRotWinkel));
						GetDlgItemText(hwnd, ID_TEXT_POLY_zRotWinkel, &G_Text_Poly_zRotWinkel[0], sizeof(G_Text_Poly_zRotWinkel));
						poly_BOOL = 1;
						DestroyWindow(hwnd);
					}
				}
				break;
			}
		}
		break;

	case WM_KEYDOWN:

		break;  



	default:
		// When no message type is handled in your application, return the default window procedure. In this case the message
		// will be handled elsewhere or not handled at all.
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}


//line
BOOL line_BOOL = 0;
char G_Text_line_l[4] = {};
char G_Text_line_phi[4] = {};
char G_Text_line_theta[4] = {};
char G_Text_line_repetitions[5] = {};
char G_Text_line_velocity[5] = {};

LRESULT CALLBACK WndProcNewLine3D(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// This switch block differentiates between the message type that could have been received. If you want to
	// handle a specific type of message in your application, just define it in this block.
	switch (msg)
	{

	case DM_GETDEFID: break;
	case DM_SETDEFID: break;
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
			switch (wParam){

			case ID_OK_KNOPF_LINE:
				{
					GetDlgItemText(hwnd, ID_TEXT_LINE_l, &G_Text_line_l[0], sizeof(G_Text_line_l));
					GetDlgItemText(hwnd, ID_TEXT_LINE_phi, &G_Text_line_phi[0], sizeof(G_Text_line_phi));
					GetDlgItemText(hwnd, ID_TEXT_LINE_theta, &G_Text_line_theta[0], sizeof(G_Text_line_theta));
					GetDlgItemText(hwnd, ID_TEXT_LINE_repetitions, &G_Text_line_repetitions[0], sizeof(G_Text_line_repetitions));
					GetDlgItemText(hwnd, ID_TEXT_LINE_velocity, &G_Text_line_velocity[0], sizeof(G_Text_line_velocity));
					line_BOOL = 1;
					DestroyWindow(hwnd);
				}
				break;

			case IDOK:
				{

					//If Enter key and Button in focus
					if ((GetDlgCtrlID(GetFocus()) == ID_OK_KNOPF_LINE)){
						GetDlgItemText(hwnd, ID_TEXT_LINE_l, &G_Text_line_l[0], sizeof(G_Text_line_l));
						GetDlgItemText(hwnd, ID_TEXT_LINE_phi, &G_Text_line_phi[0], sizeof(G_Text_line_phi));
						GetDlgItemText(hwnd, ID_TEXT_LINE_theta, &G_Text_line_theta[0], sizeof(G_Text_line_theta));
						GetDlgItemText(hwnd, ID_TEXT_LINE_repetitions, &G_Text_line_repetitions[0], sizeof(G_Text_line_repetitions));
						GetDlgItemText(hwnd, ID_TEXT_LINE_velocity, &G_Text_line_velocity[0], sizeof(G_Text_line_velocity));
						line_BOOL = 1;
						DestroyWindow(hwnd);
					}
				}
				break;
			}
		}
		break;

	case WM_KEYDOWN:

		break;



	default:
		// When no message type is handled in your application, return the default window procedure. In this case the message
		// will be handled elsewhere or not handled at all.
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}



//rectangle
BOOL rec_BOOL=0;
char G_Text_Rec_a[4];
char G_Text_Rec_b[4];
char G_Text_Rec_xRotWinkel[4];
char G_Text_Rec_zRotWinkel[4];
char G_Text_Rec_velocity[5];
char G_Text_Rec_phi0[5];

LRESULT CALLBACK WndProcNewRectangle3D(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// This switch block differentiates between the message type that could have been received. If you want to
	// handle a specific type of message in your application, just define it in this block.
	switch (msg)
	{

	case DM_GETDEFID: break;
	case DM_SETDEFID: break;
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
			switch (wParam){

			case ID_OK_KNOPF_REC:
				{
					GetDlgItemText(hwnd, ID_TEXT_REC_a, &G_Text_Rec_a[0], sizeof(G_Text_Rec_a));
					GetDlgItemText(hwnd, ID_TEXT_REC_b, &G_Text_Rec_b[0], sizeof(G_Text_Rec_b));
					GetDlgItemText(hwnd, ID_TEXT_REC_xRotWinkel, &G_Text_Rec_xRotWinkel[0], sizeof(G_Text_Rec_xRotWinkel));
					GetDlgItemText(hwnd, ID_TEXT_REC_zRotWinkel, &G_Text_Rec_zRotWinkel[0], sizeof(G_Text_Rec_zRotWinkel));
					GetDlgItemText(hwnd, ID_TEXT_REC_velocity, &G_Text_Rec_velocity[0], sizeof(G_Text_Rec_velocity));
					GetDlgItemText(hwnd, ID_TEXT_REC_phi0, &G_Text_Rec_phi0[0], sizeof(G_Text_Rec_phi0));
					rec_BOOL = 1;
					DestroyWindow(hwnd);
				}
				break;

			case IDOK:
				{

					//If Enter key and Button in focus
					if ((GetDlgCtrlID(GetFocus()) == ID_OK_KNOPF_REC)){
						GetDlgItemText(hwnd, ID_TEXT_REC_a, &G_Text_Rec_a[0], sizeof(G_Text_Rec_a));
						GetDlgItemText(hwnd, ID_TEXT_REC_b, &G_Text_Rec_b[0], sizeof(G_Text_Rec_b));
						GetDlgItemText(hwnd, ID_TEXT_REC_xRotWinkel, &G_Text_Rec_xRotWinkel[0], sizeof(G_Text_Rec_xRotWinkel));
						GetDlgItemText(hwnd, ID_TEXT_REC_zRotWinkel, &G_Text_Rec_zRotWinkel[0], sizeof(G_Text_Rec_zRotWinkel));
						GetDlgItemText(hwnd, ID_TEXT_REC_velocity, &G_Text_Rec_velocity[0], sizeof(G_Text_Rec_velocity));
						GetDlgItemText(hwnd, ID_TEXT_REC_phi0, &G_Text_Rec_phi0[0], sizeof(G_Text_Rec_phi0));
						rec_BOOL = 1;
						DestroyWindow(hwnd);
					}
				}
				break;
			}
		}
		break;

	case WM_KEYDOWN:

		break;



	default:
		// When no message type is handled in your application, return the default window procedure. In this case the message
		// will be handled elsewhere or not handled at all.
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}


