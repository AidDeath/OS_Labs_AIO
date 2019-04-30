#include "LB_06.h"


int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpszCmdLine, int nCmdShow)
{
	MSG msg;
	HWND hWnd;

	if (!Register(hInstance)) return FALSE;

	hWnd = Create(hInstance, nCmdShow);

	if (hWnd == NULL) return FALSE;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK Pr2_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		HANDLE_MSG(hWnd, WM_COMMAND, km_OnCommand);				// Комманды
		HANDLE_MSG(hWnd, WM_CLOSE, km_OnClose);					// Закрытие окна
		HANDLE_MSG(hWnd, WM_CREATE, km_OnCreate);				// Создание окна
		HANDLE_MSG(hWnd, WM_PAINT, km_OnPaint);					// Перерысовывание окна
		HANDLE_MSG(hWnd, WM_DESTROY, km_OnDestroy);				// Разрушение окна

	}

	


	return DefWindowProc(hWnd, msg, wParam, lParam);
}


BOOL Register(HINSTANCE hInst)
{
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = g_lpszClassName;
	wc.lpfnWndProc = Pr2_WndProc;
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(hInst, IDI_APPLICATION);
	wc.hCursor = LoadCursor(hInst, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);

	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, TEXT("Ошибка регистрации класса"),
			TEXT("Ошибка"), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	return TRUE;
}

HWND Create(HINSTANCE hInstance, int nCmdShow)
{
	DWORD Stl;
	Stl = WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX;

	HWND hWnd = CreateWindowEx(NULL, g_lpszClassName,
		g_lpszAplicationTitle,
		Stl,
		200,
		200,
		250,
		250,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd)
	{
		MessageBox(NULL, TEXT("Окно не создано"),
			TEXT("Ошибка"), MB_OK | MB_ICONERROR);
		return NULL;
	}

	hMutex = CreateMutex(NULL, true, "MyMutex");
	DWORD result;
	result = WaitForSingleObject(hMutex, 0);
	if (result != WAIT_OBJECT_0)
	{
		MessageBox(hWnd, TEXT("Эта программа уже запущена!"), TEXT("Второй запуск"), MB_OK);
		SendMessage(hWnd, WM_DESTROY, NULL, NULL);
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}



// WM_CREATE
BOOL km_OnCreate(HWND hWnd, LPCREATESTRUCT lpszCreateStruct)
{
	RECT rc;
	GetClientRect(hWnd, &rc);

	g_hEdit1 = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, rc.left + 10, rc.top + 30, 200, 20, hWnd, (HMENU)IDC_EDIT1, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);



	g_hButtonMain = CreateWindow(TEXT("button"), TEXT("START"), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, rc.left + 10, rc.top + 70, 100, 25, hWnd, (HMENU)IDC_BUTTON_MAIN, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
	SetFocus(g_hButtonMain);


	g_hStaticResult1 = CreateWindow(TEXT("static"), TEXT("Расчёт 1 потока"), WS_VISIBLE | WS_CHILD | SS_LEFT | WS_DISABLED, rc.left + 10, rc.top + 110, 200, 25, hWnd, (HMENU)IDC_STATIC_RESULT1, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
	g_hStaticResult2 = CreateWindow(TEXT("static"), TEXT("Расчёт 2 потока"), WS_VISIBLE | WS_CHILD | SS_LEFT | WS_DISABLED, rc.left + 10, rc.top + 145, 200, 25, hWnd, (HMENU)IDC_STATIC_RESULT2, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
	g_hStaticResult3 = CreateWindow(TEXT("static"), TEXT("Вывод результатов в Edit"), WS_VISIBLE | WS_CHILD | SS_LEFT | WS_DISABLED, rc.left + 10, rc.top + 180, 200, 25, hWnd, (HMENU)IDC_STATIC_RESULT3, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);



	return TRUE;
}

// WM_ONPAINT
void km_OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(hWnd, &ps);
	RECT rc;
	GetClientRect(hWnd, &rc);


	EndPaint(hWnd, &ps);
}

// WM_ONCLOSE
void km_OnClose(HWND hWnd)
{
	DestroyWindow(hWnd);
	SetEvent(hEvent);
}

// WM_DESTROY
void km_OnDestroy(HWND hWnd)
{
	ReleaseMutex(hMutex);
	CloseHandle(hMutex);
	PostQuitMessage(0);
}

// WM_COMMAND
void km_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
	TCHAR buff[200];
	DWORD dwNumbOfBytes = MAX_BYTES;
	wsprintf(buff, TEXT("%d"), id);

	switch (id)
	{
	case IDC_BUTTON_MAIN:
	{
		int param1 = 2,  param3 = 16;
			
		InitializeCriticalSection(&g_cs);

			hSem = CreateSemaphore(NULL, 1, 1, "For calc");
			hSem2 = CreateSemaphore(NULL, 1, 1, "For output");
			hEvent = CreateEvent(NULL, TRUE, TRUE, "Closing");

			hThread1 = CreateThread(NULL, 0L, ThreadProc, &param1, 0L, &Thread1_ID);
			hThread3 = CreateThread(NULL, 0L, ThreadProc, &param3, 0L, &Thread3_ID);
			hThread4 = CreateThread(NULL, 0L, ThreadOut, NULL, CREATE_SUSPENDED, &Thread4_ID);
			Button_Enable(g_hButtonMain, FALSE);
		
	}
	break;
	

	
	default:
	{
		//MessageBox(hWnd, TEXT("Стандартная функция"), buff, MB_OK);
	}
	break;
	}
}

DWORD WINAPI ThreadProc(PVOID pvParam)  
{
	int* type;
	type = (int*)pvParam;
	int x; 
	TCHAR buf[200];



	switch (*type)
	{
	
	case 2:
	{


		do
		{
		WaitForSingleObject(hSem, INFINITE);

		Static_Enable(g_hStaticResult1, TRUE);
		x = (int)rand();
		getBin(x, buf);
		Sleep(200);
		Static_Enable(g_hStaticResult1, FALSE);
		ReleaseSemaphore(hSem, 1, NULL);

		DWORD Time2Die = WaitForSingleObject(hEvent, 0);
		if (Time2Die != WAIT_OBJECT_0)
		{
			break;
		}

		EnterCriticalSection(&g_cs);
		if (ptrRow < 30)		// Помещение результатов в массив, в крит. секции
		{
			strcpy_s(Results[ptrRow++], buf);
		}
		else
		{
			Static_Enable(g_hStaticResult3, TRUE);
			//ReleaseSemaphore(hSem2, 1, NULL);
			ResumeThread(hThread4);

			SuspendThread(hThread3);
			LeaveCriticalSection(&g_cs);
			SuspendThread(hThread1);

		}
		LeaveCriticalSection(&g_cs);
		
		} while (true);

	}
	break;

	case 16:
	{
	
		do
		{
			WaitForSingleObject(hSem, INFINITE);
	
			Static_Enable(g_hStaticResult2, TRUE);
			x = (int)rand();
			getHex(x, *buf);
			Sleep(200);
			Static_Enable(g_hStaticResult2, FALSE);
			ReleaseSemaphore(hSem, 1, NULL);

			DWORD Time2Die = WaitForSingleObject(hEvent, 0);
			if (Time2Die != WAIT_OBJECT_0)
			{
				break;
			}

			EnterCriticalSection(&g_cs);
			if (ptrRow < 30)
			{
				strcpy_s(Results[ptrRow++], buf);
			}
			else
			{

				Static_Enable(g_hStaticResult3, TRUE);
				//ReleaseSemaphore(hSem2, 1, NULL);
				ResumeThread(hThread4);


				SuspendThread(hThread1);
				LeaveCriticalSection(&g_cs);
				SuspendThread(hThread3);

			}
			LeaveCriticalSection(&g_cs);
			
		

		}
		while (true);
	}
	break;
	default:
		break;
	}
	return(0);
}

DWORD WINAPI ThreadOut(PVOID pvParam)
{
	TCHAR buf[30];
	do
	{
	//	WaitForSingleObject(hSem2, INFINITE);
		Static_Enable(g_hStaticResult1, FALSE);
		Static_Enable(g_hStaticResult2, FALSE);

		if (ptrRow == 0)
		{
			Edit_SetText(g_hEdit1, Results[ptrRow]);
			Static_Enable(g_hStaticResult3, FALSE);

			

			ResumeThread(hThread1);
			ResumeThread(hThread3);
			
			SuspendThread(hThread4);

 		}
		if (ptrRow > 0)
		{
			Edit_SetText(g_hEdit1, Results[ptrRow--]);
		}
		

		DWORD Time2Die = WaitForSingleObject(hEvent, 0);
		if (Time2Die != WAIT_OBJECT_0)
		{
			break;
		}

	Sleep(200);

	} while (true);
	return(0);
}
