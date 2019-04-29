#pragma once
#pragma comment(lib,"../x64/Debug/LB_01_DLL_16.lib")
#pragma comment(lib,"../x64/Debug/LB_01_DLL_8.lib")
#pragma comment(lib,"../x64/Debug/LB_01_DLL_2.lib")

#include "../LB_01_DLL_16/LB_01_DLL_16.h"
#include "../LB_01_DLL_8/LB_01_DLL_8.h"
#include "../LB_01_DLL_2/LB_01_DLL_2.h"

#include <Windows.h>
#include <tchar.h>
#include "windowsx.h"
#include "WinUser.h"
#include "stdio.h"

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
DWORD WINAPI ThreadProc(PVOID pvParam);
DWORD WINAPI ThreadOut(PVOID pvParam);
/*-------------------------------------------------------------------*/


//-- Global Variables ------------ 
LPCTSTR g_lpszClassName = TEXT("sp_pr2_class");
LPCTSTR g_lpszlistboxClassName = TEXT("Button");
LPCTSTR g_lpszAplicationTitle = TEXT("Заголовок окна");
LPCTSTR g_lpszDestroyTitle = TEXT("Разрушение название");
LPCTSTR g_lpszDestroyMessage = TEXT("Произошло разрушение окна WM_DESTROY");


#define MAX_BYTES  10000

TCHAR lpszFileSpec[256];
TCHAR Buffer[MAX_BYTES] = TEXT("Окно");

TCHAR Results[30][30];  // массив из 30 строк длинной в 20 символов

int ptrRow = 0;
 
CRITICAL_SECTION g_cs;

/*----------------THREADS-------------------*/
HANDLE hThread1 = NULL;
HANDLE hThread3 = NULL;
HANDLE hThread4 = NULL;

HANDLE hSem = NULL;
HANDLE hSem2 = NULL;


DWORD Thread1_ID;
DWORD Thread3_ID;
DWORD Thread4_ID;




/*--------------------------------------------*/

/*-----------CONTROLS------------------------*/
HWND g_hEdit1;


HWND g_hButtonMain;



HWND g_hStaticResult1;
HWND g_hStaticResult2;
HWND g_hStaticResult3;


#define IDC_EDIT1			40100
#define IDC_BUTTON_MAIN		40101





#define IDC_STATIC_RESULT1	40102
#define IDC_STATIC_RESULT2	40103
#define IDC_STATIC_RESULT3	40104




