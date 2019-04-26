#include "LB_05.h"


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
		500,
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

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}



// WM_CREATE
BOOL km_OnCreate(HWND hWnd, LPCREATESTRUCT lpszCreateStruct)
{
	RECT rc;
	GetClientRect(hWnd, &rc);

	g_hEdit1 = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, rc.left + 10, rc.top + 30, 150, 20, hWnd, (HMENU)IDC_EDIT1, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
	//SetFocus(g_hEdit1);
	g_hEdit2 = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, rc.left + 170, rc.top + 30, 150, 20, hWnd, (HMENU)IDC_EDIT2, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
	g_hEdit3 = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, rc.left + 330, rc.top + 30, 150, 20, hWnd, (HMENU)IDC_EDIT3, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);



	g_hButtonMain = CreateWindow(TEXT("button"), TEXT("START"), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, rc.left + 10, rc.top + 70, 100, 25, hWnd, (HMENU)IDC_BUTTON_MAIN, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
	SetFocus(g_hButtonMain);
	g_hButtonPause = CreateWindow(TEXT("button"), TEXT("STOP"), WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_DISABLED, rc.left + 170, rc.top + 70, 100, 25, hWnd, (HMENU)IDC_BUTTON_STOP, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
	g_hButtonStop = CreateWindow(TEXT("button"), TEXT("PAUSE/RESUME"), WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_DISABLED, rc.left + 330, rc.top + 70, 120, 25, hWnd, (HMENU)IDC_BUTTON_PAUSE, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

	g_hStaticResult1 = CreateWindow(TEXT("static"), TEXT("speed1"), WS_VISIBLE | WS_CHILD | SS_LEFT, rc.left + 10, rc.top + 110, 150, 25, hWnd, (HMENU)IDC_STATIC_RESULT1, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
	g_hStaticResult2 = CreateWindow(TEXT("static"), TEXT("speed2"), WS_VISIBLE | WS_CHILD | SS_LEFT, rc.left + 170, rc.top + 110, 150, 25, hWnd, (HMENU)IDC_STATIC_RESULT2, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
	g_hStaticResult3 = CreateWindow(TEXT("static"), TEXT("speed3"), WS_VISIBLE | WS_CHILD | SS_LEFT, rc.left + 330, rc.top + 110, 150, 25, hWnd, (HMENU)IDC_STATIC_RESULT3, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

	
	g_hBtn1Up = CreateWindow(TEXT("button"), TEXT(">"), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, rc.left + 10, rc.top + 150, 25, 25, hWnd, (HMENU)IDC_BTN1UP, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
	g_hBtn1Down = CreateWindow(TEXT("button"), TEXT("<"), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, rc.left + 35, rc.top + 150, 25, 25, hWnd, (HMENU)IDC_BTN1DOWN, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
	g_hBtn2Up = CreateWindow(TEXT("button"), TEXT(">"), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, rc.left + 170, rc.top + 150, 25, 25, hWnd, (HMENU)IDC_BTN2UP, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
	g_hBtn2Down = CreateWindow(TEXT("button"), TEXT("<"), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, rc.left + 195, rc.top + 150, 25, 25, hWnd, (HMENU)IDC_BTN2DOWN, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
	g_hBtn3Up = CreateWindow(TEXT("button"), TEXT(">"), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, rc.left + 330, rc.top + 150, 25, 25, hWnd, (HMENU)IDC_BTN3UP, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
	g_hBtn3Down = CreateWindow(TEXT("button"), TEXT("<"), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, rc.left + 355, rc.top + 150, 25, 25, hWnd, (HMENU)IDC_BTN3DOWN, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

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
/*	if (ThreadStatus)
	{
		TerminateThread(hThread1, 1);
		CloseHandle(hThread1);
		TerminateThread(hThread2, 1);
		CloseHandle(hThread2);
		TerminateThread(hThread3, 1);
		CloseHandle(hThread3);
		TerminateThread(hThread4, 1);
		CloseHandle(hThread4);

	}
	*/
	DestroyWindow(hWnd);
}

// WM_DESTROY
void km_OnDestroy(HWND hWnd)
{
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
	{/*нужно запустить три потока, указать им начальную ф-цию с разными параметрами*/
		int param1 = 2, param2 = 8, param3 = 16;


			hThread1 = CreateThread(NULL, 0L, ThreadProc, &param1, 0L, &Thread1_ID);
			hThread2 = CreateThread(NULL, 0L, ThreadProc, &param2, 0L, &Thread2_ID);
			hThread3 = CreateThread(NULL, 0L, ThreadProc, &param3, 0L, &Thread3_ID);
			Button_Enable(g_hButtonMain, FALSE);
			Button_Enable(g_hButtonStop, TRUE);
			Button_Enable(g_hButtonPause, TRUE);
			
			DWORD Thec;
			GetExitCodeThread(hThread4, &Thec);

			if (Thec != STILL_ACTIVE) 
			{
				hThread4 = CreateThread(NULL, 0L, ThreadSpeed, NULL, 0L, &Thread4_ID);
			}
		
	}
	break;
	case IDC_BUTTON_STOP:
	{
		TerminateThread(hThread1, 1);
		CloseHandle(hThread1);
		TerminateThread(hThread2, 1);
		CloseHandle(hThread2);
		TerminateThread(hThread3, 1);
		CloseHandle(hThread3);
		Button_Enable(g_hButtonMain, TRUE);
		Button_Enable(g_hButtonStop, FALSE);
		Button_Enable(g_hButtonPause, FALSE);

		
	}
	break;
	case IDC_BUTTON_PAUSE:
	{
		if (ThreadStatus)
		{
			SuspendThread(hThread1);
			SuspendThread(hThread2);
			SuspendThread(hThread3);
			ThreadStatus = FALSE;
		}
		else
		{
			ResumeThread(hThread1);
			ResumeThread(hThread2);
			ResumeThread(hThread3);
			ThreadStatus = TRUE;
		}

	}
	break;
	case IDC_BTN1UP:
	{

	}
	break;
	case IDC_BTN1DOWN:
	{
		int i = GetThreadPriority(hThread1);
		SetThreadPriority(hThread1, --i);
	}
	break;
	case IDC_BTN2UP:
	{

	}
	break;
	case IDC_BTN2DOWN:
	{

	}
	break;
	case IDC_BTN3UP:
	{

	}
	break;
	case IDC_BTN3DOWN:
	{

	}
	break;
	default:
	{
		//MessageBox(hWnd, TEXT("Стандартная функция"), buff, MB_OK);
	}
	break;
	}
}

DWORD WINAPI ThreadProc(PVOID pvParam)   /*Сюда передадим параметр, который укажет, какую ф-цию запускать в потоке.
				   Далее ф-ция создаст рандомное число и передаст его в библиотечную ф-цию.
				   Получит результат от неё и впишет в эдит*/
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
		x = (int)rand();
		getBin(x, buf);
		Edit_SetText(g_hEdit1, buf);
		Counter1++;
		Sleep(50);
		} while (true);
	}
	break;
	case 8:
	{
		do
		{
		x = (int)rand();
		char* temp = &getOct(x);
		wsprintf(buf, TEXT("%s"), temp);
		Edit_SetText(g_hEdit2, buf);
		Counter2++;
		Sleep(50);
		} while (true);
	}
	break;
	case 16:
	{
		do
		{
		x = (int)rand();
		getHex(x, *buf);
		Edit_SetText(g_hEdit3, buf);
		Counter3++;
		Sleep(50);
	} while (true);
	}
	break;
	default:
		break;
	}
	return(0);
}

DWORD WINAPI ThreadSpeed(PVOID pvParam)
{
	TCHAR buf[30];
	do
	{
	Sleep(1000);
	
		_itoa_s(Counter1, buf,10);
		Static_SetText(g_hStaticResult1, buf);

		_itoa_s(Counter2, buf, 10);
		Static_SetText(g_hStaticResult2, buf);

		_itoa_s(Counter3, buf, 10);
		Static_SetText(g_hStaticResult3, buf);
		Counter1 = Counter2 = Counter3 = 0;

	} while (true);
	return(0);
}