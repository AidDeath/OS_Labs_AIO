#pragma once

#include <Windows.h>
#include <tchar.h>
#include "windowsx.h"
#include "WinUser.h"
#include "stdio.h"
#include <iostream>
#include <fstream>
#include "processthreadsapi.h"

LRESULT CALLBACK Pr2_WndProc(HWND, UINT, WPARAM, LPARAM);
/* Регистрация окна */
BOOL Register(HINSTANCE);
/* Создание окна */
HWND Create(HINSTANCE, int);


/* Прототипы */
/*--- WM_CREATE -----------------------------------------------------*/
BOOL km_OnCreate(HWND hWnd, LPCREATESTRUCT lpszCreateStruct);
/*--- WM_DESTROY -----------------------------------------------------*/
void km_OnDestroy(HWND hWnd);
/*--- WM_PAINT -------------------------------------------------------*/
void km_OnPaint(HWND hWnd);
/*--- WM_CLOSE -------------------------------------------------------*/
void km_OnClose(HWND hWnd);
/*--- WM_COMMAND ----------------------------------------------------------*/
void km_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify);
/*--------------------------------------------------------------------*/


//-- Global Variables ------------ 
LPCTSTR g_lpszClassName = TEXT("sp_pr2_class");
LPCTSTR g_lpszlistboxClassName = TEXT("Button");
LPCTSTR g_lpszAplicationTitle = TEXT("Заголовок окна");
LPCTSTR g_lpszDestroyTitle = TEXT("Разрушение название");
LPCTSTR g_lpszDestroyMessage = TEXT("Произошло разрушение окна WM_DESTROY");




HWND g_hEdit;

HWND g_hButtonMain;

HWND g_hStaticResult;

HWND g_hCheckBox;


#define IDC_EDIT			40100
#define IDC_BUTTON_MAIN		40101
#define IDC_STATIC_RESULT	40102
#define IDC_CHECKBOX		40103


