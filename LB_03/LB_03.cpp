#include "LB_03.h"
#include "stdio.h"
#include "windef.h"
#include "winuser.h"

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
	
	case WM_ACTIVATE:
	{		// При изменении статуса активации окна выставляем прозрачность.
		if (LOWORD(wParam) == WA_CLICKACTIVE || LOWORD(wParam) == WA_ACTIVE)
		{
			SetLayeredWindowAttributes(hWnd, 0, 255, LWA_ALPHA);
		}
		if (LOWORD(wParam) == WA_INACTIVE)
		{
			SetLayeredWindowAttributes(hWnd, 0, 204, LWA_ALPHA);
		}
	}
	break;

/*	case WM_LBUTTONDOWN:
	{		// Перетаскивание окна за любой участок
		// ---------------------------------------------------------
		// Посылаем сообщение окну, чтобы оно думало, что кликнули по его заголовку.
		// ---------------------------------------------------------
		SendMessage(hWnd, WM_NCLBUTTONDOWN, HTCAPTION, NULL);
		break;
	}
*/



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
		Stl = WS_OVERLAPPED | WS_BORDER | WS_SYSMENU;
//	Stl = WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX;
	//	Stl = WS_DISABLED;

	HWND hWnd = CreateWindowEx(WS_EX_LAYERED | WS_EX_TOPMOST, g_lpszClassName,
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
	g_hEdit = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, rc.left + 10, rc.top + 10, 150, 20, hWnd, (HMENU)IDC_EDIT, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
	SetFocus(g_hEdit);

	g_hButtonMain = CreateWindow(TEXT("button"), TEXT("OK"), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, rc.left + 10, rc.top + 40, 100, 25, hWnd, (HMENU)IDC_BUTTON_MAIN, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
	SetFocus(g_hButtonMain);

	g_hRadioBin = CreateWindow(TEXT("button"), TEXT("BIN"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, rc.left + 10, rc.top + 80, 100, 25, hWnd, (HMENU)IDC_RADIO_BIN, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
	g_hRadioThree = CreateWindow(TEXT("button"), TEXT("THREE"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, rc.left + 10, rc.top + 100, 100, 25, hWnd, (HMENU)IDC_RADIO_THREE, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
	g_hRadioOct = CreateWindow(TEXT("button"), TEXT("OCT"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, rc.left + 10, rc.top + 120, 100, 25, hWnd, (HMENU)IDC_RADIO_OCT, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
	g_hRadioHex = CreateWindow(TEXT("button"), TEXT("HEX"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, rc.left + 10, rc.top + 140, 100, 25, hWnd, (HMENU)IDC_RADIO_HEX, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

	g_hStaticResult = CreateWindow(TEXT("static"), TEXT("Результат: 0"), WS_VISIBLE | WS_CHILD | SS_LEFT, rc.left + 180, rc.top + 10, 250, 25, hWnd, (HMENU)IDC_STATIC_RESULT, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);


//	HWND g_hStaticResult1 = CreateWindow(TEXT("static"), TEXT("Результат: 0"), WS_VISIBLE | WS_CHILD | SS_LEFT, rc.left + 180, rc.top + 50, 250, 25, hWnd, (HMENU)IDC_TRANSPARENSY, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

//	g_hTransparensy = CreateWindow(TEXT("static"), TEXT("Transparensy"), WS_VISIBLE | WS_CHILD | SS_LEFT, rc.left + 180, rc.top + 50, 250, 50, hWnd, (HMENU)IDC_TRANSPARENSY, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
//	g_hTransparensy = CreateWindowEx(WS_EX_LAYERED, TEXT("static"), TEXT("Transpahensy"), WS_VISIBLE | WS_CHILD | SS_LEFT, rc.left + 180, rc.top + 50, 250,50,hWnd, (HMENU)IDC_TRANSPARENSY, (HINSTANCE)GetWindowLongPtr(hWnd,GWLP_HINSTANCE), NULL );


	Button_Enable(g_hRadioBin, FALSE);
	Button_Enable(g_hRadioThree, FALSE);
	Button_Enable(g_hRadioOct, FALSE);
	Button_Enable(g_hRadioHex, FALSE);

	HANDLE  hFindFile;
	WIN32_FIND_DATA  fd;

	// находим первый файл
	hFindFile = FindFirstFile(TEXT("..\\x64\\Debug\\*.dll"), &fd);

	if (INVALID_HANDLE_VALUE == hFindFile)
	{
		MessageBox(hWnd, TEXT("Ошибка поиска файла"), TEXT("Ошибка"), MB_OK);
	}

	do
	{
		// ПОДКЛЮЧЕНИЕ БИБЛИОТЕКИ
		if (&fd != NULL)
		{
			HINSTANCE hLib = LoadLibrary(fd.cFileName);
			if (hLib == NULL)
			{
				MessageBox(hWnd, TEXT("Ошибка при загрузке DLL"), TEXT("error"), MB_OK);
			}
			else
			{
				SenseOfExisting = (pSenseOfExisting)GetProcAddress(hLib, "SenseOfExisting");
				int	sense = SenseOfExisting();

				switch (sense)
				{
				case (2):
				{
					//activate binary controls
					Button_Enable(g_hRadioBin, TRUE);
					getBin = (pGetBin)GetProcAddress(hLib, "getBin");
					break;
				}
				case (3):
				{
					//activate triple controls
					Button_Enable(g_hRadioThree, TRUE);
					getThree = (pGetThree)GetProcAddress(hLib, "getThree");
					break;
				}
				case (8):
				{
					//activate octagon controls
					Button_Enable(g_hRadioOct, TRUE);
					getOct = (pGetOct)GetProcAddress(hLib, "getOct");
					break;
				}
				case (16):
				{
					// activate hexademical controls
					Button_Enable(g_hRadioHex, TRUE);
					getHex = (pGetHex)GetProcAddress(hLib, "getHex");
					break;
				}
				default:
				{
					// smth went wrong, not returned 2 3 8 16
					break;
				}
				}

			}
		}

	} 
	while (FindNextFile(hFindFile, &fd));

	if (getBin != NULL)
	{
		Button_SetCheck(g_hRadioBin, BM_SETCHECK);
	}
	else if (getThree != NULL)
	{
		Button_SetCheck(g_hRadioThree, BM_SETCHECK);
	}
	else if (getOct != NULL)
	{
		Button_SetCheck(g_hRadioOct, BM_SETCHECK);
	}
	else if (getHex != NULL)
	{
		Button_SetCheck(g_hRadioHex, BM_SETCHECK);
	}
	else
	{
		Button_Enable(g_hButtonMain, FALSE);
	}

	return TRUE;
}

// WM_ONPAINT
void km_OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(hWnd, &ps);
	RECT rc;
	GetClientRect(hWnd, &rc);


	// Скругление углов окна
	HRGN hWholeWnd = CreateRoundRectRgn(rc.left, rc.top, 500, 250, 20, 20);

	HRGN hTransparent = CreateRoundRectRgn(rc.left + 180, rc.top + 100, rc.left + 380, rc.top + 170, 10, 10);


	HRGN hResultRGN = CreateRoundRectRgn(0, 0, 0, 0, 0, 0);
	CombineRgn(hResultRGN, hWholeWnd, hTransparent, RGN_DIFF);
	SetWindowRgn(hWnd, hResultRGN , TRUE);

//	

/*-------------------------------------------------------------------------------*/
	/*
	RECT rc1;
	// Получаем размер клиентской прозрачной части
	GetClientRect(g_hTransparensy, &rc1);
	HRGN hRgn = CreateRoundRectRgn(rc1.left, rc1.top, rc1.right, rc1.bottom, 10, 10);
	HDC hDC1 = GetDC(g_hTransparensy);
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
	FrameRgn(hDC1, hRgn, hBrush, 1, 1);
	//SetLayeredWindowAttributes(g_hTransparensy, 0, 100, LWA_ALPHA | LWA_COLORKEY);
	SetWindowRgn(g_hTransparensy, hRgn ,TRUE);

//	SetLayeredWindowAttributes(g_hStaticForEllipse, 0, 100, LWA_ALPHA | LWA_COLORKEY);
	*/
/*--------------------------------------------------------------------------------*/

	EndPaint(hWnd, &ps);
}

// WM_ONCLOSE
void km_OnClose(HWND hWnd)
{
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
	{
		TCHAR string[200];
		TCHAR buf[200];
		GetWindowText(g_hEdit, string, sizeof(string));
		int x = atoi(string);


		if (Button_GetCheck(g_hRadioBin))
		{
			getBin(x, buf);
		}

		if (Button_GetCheck(g_hRadioThree))
		{
			char* temp;
			temp = getThree(x);
			wsprintf(buf, TEXT("%s"), temp);
		}

		if (Button_GetCheck(g_hRadioOct))
		{
			char* temp = &getOct(x);
			wsprintf(buf, TEXT("%s"), temp);
		}

		if (Button_GetCheck(g_hRadioHex))
		{
			getHex(x, *buf);
		}

		TCHAR result[200];
		wsprintf(result, TEXT("Результат: %s"), buf);
		Static_SetText(g_hStaticResult, result);
	}
	break;
	default:
	{
		//MessageBox(hWnd, TEXT("Стандартная функция"), buff, MB_OK);
	}
	break;
	}
}


