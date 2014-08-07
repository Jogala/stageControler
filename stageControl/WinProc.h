#include "Header.h"

#define ID_OK_KNOPF				1000

#define ID_TEXT_POLY_R			1
#define ID_TEXT_POLY_phi0		2
#define ID_TEXT_POLY_velocity	3
#define ID_TEXT_POLY_steps		4


#ifndef KEYBOARDHOOK_H
#define KEYBOARDHOOK_H
LRESULT CALLBACK WndProcNewPoly3D(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif

extern  char G_Text_Poly_R[3];
extern  char G_Text_Poly_phi0[3];
extern  char G_Text_Poly_velocity[3];
extern  char G_Text_Poly_steps[3];
