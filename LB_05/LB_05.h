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
DWORD WINAPI ThreadSpeed(PVOID pvParam);
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
/*----------------THREADS-------------------*/
HANDLE hThread1 = NULL;
HANDLE hThread2 = NULL;
HANDLE hThread3 = NULL;
HANDLE hThread4 = NULL;

DWORD Thread1_ID;
DWORD Thread2_ID;
DWORD Thread3_ID;
DWORD Thread4_ID;

BOOL ThreadStatus = TRUE;

int Counter1 = 0, Counter2 = 0, Counter3 = 0;
/*--------------------------------------------*/

/*-----------CONTROLS------------------------*/
HWND g_hEdit1;
HWND g_hEdit2;
HWND g_hEdit3;

HWND g_hButtonMain;
HWND g_hButtonStop;
HWND g_hButtonPause;


HWND g_hStaticResult1;
HWND g_hStaticResult2;
HWND g_hStaticResult3;


#define IDC_EDIT1			40100
#define IDC_EDIT2			40101
#define IDC_EDIT3			40102


#define IDC_BUTTON_MAIN		40103
#define IDC_BUTTON_STOP		40104
#define IDC_BUTTON_PAUSE	40105



#define IDC_STATIC_RESULT1	40106
#define IDC_STATIC_RESULT2	40107
#define IDC_STATIC_RESULT3	40108






/* Итого:

Делаем окно, в нёи три Эдита, кнопки старт и пауза. Под эдитами три статик текста. Под статик текстами UpDownы или комбобоксы
Нажатие на старт запускает три потока, потоки выводят результат  в эдиты, каждый в свой.
В статик текстах отображается текущая скорость потоков, обновляется каждую секунду (Это должен делать ещё один, отдельный поток)
 При изменении АпДаунов меняется приоритет того или иного потока.
Нажатие на паузу присостанавливает все потоки, либо обратно запускает их
нужно предумиотреть завершение всех потоков перед выходом из программы.*/