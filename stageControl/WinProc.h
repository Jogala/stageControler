#include "Header.h"

#define ID_OK_KNOPF_POLY		1000
#define	ID_OK_KNOPF_LINE		1001
#define	ID_OK_KNOPF_REC			1002

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
#define ID_TEXT_LINE_repetitions	14
#define ID_TEXT_LINE_velocity		15



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





//////////////////////////////////////////////////////
//					rectangle						//
//////////////////////////////////////////////////////
#define ID_TEXT_REC_a				21
#define ID_TEXT_REC_b				22
#define ID_TEXT_REC_xRotWinkel		23
#define ID_TEXT_REC_zRotWinkel		24
#define ID_TEXT_REC_velocity		25

extern	BOOL rec_BOOL;
extern  char G_Text_Rec_a[4];
extern  char G_Text_Rec_b[4];
extern  char G_Text_Rec_xRotWinkel[4];
extern  char G_Text_Rec_zRotWinkel[4];
extern  char G_Text_Rec_velocity[5];


#ifndef Rec3D_H 
#define Rec3D_H
LRESULT CALLBACK WndProcNewRectangle3D(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif


