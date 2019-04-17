#pragma once

#include <Windows.h>
#include <tchar.h>
#include "resource.h"
#include "windowsx.h"
#include "WinUser.h"

//-- Prototypes -------------------
BOOL CALLBACK ModAboutDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK ModLoadDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK LoadBmpDlgProc(HWND, UINT, WPARAM, LPARAM);

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
/*--- WM_LBUTTONDOWN , WM_LBUTTONDBCLK -------------------------------*/
void km_OnLButtonDown(HWND hWnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);
/*--- WM_RBUTTONDOWN , WM_RBUTTONDBCLK -------------------------------*/
void km_OnRButtonDown(HWND hWnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);
/*--- WM_PAINT -------------------------------------------------------*/
void km_OnPaint(HWND hWnd);
/*--- WM_CLOSE -------------------------------------------------------*/
void km_OnClose(HWND hWnd);
/*--- WM_MENUSELECT -------------------------------------------------------*/
void km_OnMenuSelect(HWND hWnd, HMENU hmenu, int item, HMENU hmenuPopup, UINT flags);
/*--- WM_COMMAND ----------------------------------------------------------*/
void km_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify);
/*--------------------------------------------------------------------*/


//-- Global Variables ------------ 
LPCTSTR g_lpszClassName = TEXT("sp_pr2_class");
LPCTSTR g_lpszlistboxClassName = TEXT("Button");
LPCTSTR g_lpszAplicationTitle = TEXT("Заголовок окна");
LPCTSTR g_lpszDestroyTitle = TEXT("Разрушение название");
LPCTSTR g_lpszDestroyMessage = TEXT("Произошло разрушение окна WM_DESTROY");


#define MAX_BYTES  10000

TCHAR lpszFileSpec[256];
TCHAR Buffer[MAX_BYTES] = TEXT("Окно");

HWND g_hwndDlg; // Диалоговое окно
HANDLE g_hFile = NULL;

// Global variables
HMENU		g_lpszMainMenu;
HMENU		g_lpszFileMenu;
HMENU		g_lpszViewMenu;

HWND g_hEdit;

HWND g_hButtonMain;
HWND g_hRadioBin;
HWND g_hRadioThree;
HWND g_hRadioOct;
HWND g_hRadioHex;

HWND g_hStaticResult;

#define IDC_EDIT			40100
#define IDC_BUTTON_MAIN		40101

#define IDC_RADIO_BIN		40102
#define IDC_RADIO_THREE		40103
#define IDC_RADIO_OCT		40104
#define IDC_RADIO_HEX		40105

#define IDC_STATIC_RESULT	40106

typedef void(*pGetBin)(int x, char*);
typedef char*(*pGetThree)(int x);
typedef char&(*pGetOct)(int x);
typedef void(*pGetHex)(int x, char&);
typedef int(*pSenseOfExisting)();

pGetBin getBin;
pGetThree getThree;
pGetOct getOct;
pGetHex getHex;
pSenseOfExisting SenseOfExisting;