#include "Header.h"

#define ID_OK_KNOPF_POLY		1000
#define	ID_OK_KNOPF_LINE		1001

//////////////////////////////////////////////////////
//					polygon							//
//////////////////////////////////////////////////////
#define ID_TEXT_POLY_R			1
#define ID_TEXT_POLY_phi0		2
#define ID_TEXT_POLY_steps		3
#define ID_TEXT_POLY_xRotWinkel	4
#define ID_TEXT_POLY_zRotWinkel	5
#define ID_TEXT_POLY_velocity	6



extern	BOOL poly_BOOL;
extern  char G_Text_Poly_R[4];
extern  char G_Text_Poly_phi0[4];
extern  char G_Text_Poly_steps[5];
extern  char G_Text_Poly_xRotWinkel[5];
extern  char G_Text_Poly_zRotWinkel[5];
extern  char G_Text_Poly_velocity[5];


#ifndef Poly3D_H 
#define Poly3D_H
LRESULT CALLBACK WndProcNewPoly3D(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif

//////////////////////////////////////////////////////
//					line							//
//////////////////////////////////////////////////////
#define ID_TEXT_LINE_l				11
#define ID_TEXT_LINE_phi			12
#define ID_TEXT_LINE_theta			13
#define ID_TEXT_LINE_repetitions	15
#define ID_TEXT_LINE_velocity		14



extern	BOOL line_BOOL;
extern  char G_Text_line_l[4];
extern  char G_Text_line_phi[4];
extern  char G_Text_line_theta[4];
extern  char G_Text_line_repetitions[5];
extern  char G_Text_line_velocity[5];


#ifndef Line3D_H 
#define Line3D_H
LRESULT CALLBACK WndProcNewLine3D(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif


