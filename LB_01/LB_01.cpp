#include "LB_01.h"
#include "stdio.h"

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpszCmdLine, int nCmdShow)
{
	MSG msg;
	HWND hWnd;

	if (!Register(hInstance)) return FALSE;

	hWnd = Create(hInstance, nCmdShow);

	if (hWnd == NULL) return FALSE;

	HACCEL hAccel;
	hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));


	g_hwndDlg = (HWND)0;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (g_hwndDlg == 0 || !IsDialogMessage(g_hwndDlg, &msg))
		{
			if (!TranslateAccelerator(hWnd, hAccel, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK Pr2_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		HANDLE_MSG(hWnd, WM_COMMAND, km_OnCommand);				// Комманды
		HANDLE_MSG(hWnd, WM_MENUSELECT, km_OnMenuSelect);		// Смена меню
		HANDLE_MSG(hWnd, WM_CLOSE, km_OnClose);					// Закрытие окна
		HANDLE_MSG(hWnd, WM_LBUTTONDOWN, km_OnLButtonDown);		// Левая кнопка мыши нажата
		HANDLE_MSG(hWnd, WM_RBUTTONDOWN, km_OnRButtonDown);		// Правая кнопка мыши нажата
		HANDLE_MSG(hWnd, WM_CREATE, km_OnCreate);				// Создание окна
		HANDLE_MSG(hWnd, WM_PAINT, km_OnPaint);					// Перерысовывание окна
		HANDLE_MSG(hWnd, WM_DESTROY, km_OnDestroy);				// Разружение окна
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
	//HBRUSH hbr;
	//hbr = CreateSolidBrush();
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

	g_lpszMainMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));

	HWND hWnd = CreateWindowEx(NULL /*| WS_EX_TRANSPARENT*/, g_lpszClassName,
		g_lpszAplicationTitle,
		Stl,
		200,
		200,
		500,
		250,
		NULL,
		g_lpszMainMenu,
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
	//MessageBox(hWnd, TEXT("WM_CREATE"), g_lpszDestroyTitle, MB_OK | MB_ICONEXCLAMATION);

	g_lpszFileMenu = GetSubMenu(g_lpszMainMenu, 0);
	g_lpszViewMenu = GetSubMenu(g_lpszMainMenu, 1);


	RECT rc;
	GetClientRect(hWnd, &rc);



	//SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 200, LWA_COLORKEY | LWA_ALPHA);

	//int x1, y1, x2, y2;
	//RECT rect;
	//POINT pointtop, pointbottom;

	//GetClientRect(hWnd, &rect);
	////Get The Coordinates of the Window.
	//
	//pointtop = { rect.left,rect.top };
	//pointbottom = { rect.right, rect.bottom };

	////Break the Coordinates into four different variables.
	//x1 = pointtop.x;
	//y1 = pointtop.y;
	//x2 = pointbottom.x;
	//y2 = pointbottom.y;


	//HRGN region = CreateRoundRectRgn(x1, y1, x2, y2 , 50,50);
	//SetWindowRgn(hWnd, region, TRUE);


	g_hEdit = CreateWindow(TEXT("edit"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT, rc.left + 10, rc.top + 10, 150, 20, hWnd, (HMENU)IDC_EDIT, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
	SetFocus(g_hEdit);

	g_hButtonMain = CreateWindow(TEXT("button"), TEXT("OK"), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, rc.left + 10, rc.top + 40, 100, 25, hWnd, (HMENU)IDC_BUTTON_MAIN, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
	SetFocus(g_hButtonMain);

	g_hRadioBin = CreateWindow(TEXT("button"), TEXT("BIN"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, rc.left + 10, rc.top + 80, 100, 25, hWnd, (HMENU)IDC_RADIO_BIN, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
	g_hRadioThree = CreateWindow(TEXT("button"), TEXT("THREE"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, rc.left + 10, rc.top + 100, 100, 25, hWnd, (HMENU)IDC_RADIO_THREE, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
	g_hRadioOct = CreateWindow(TEXT("button"), TEXT("OCX"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, rc.left + 10, rc.top + 120, 100, 25, hWnd, (HMENU)IDC_RADIO_OCT, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
	g_hRadioHex = CreateWindow(TEXT("button"), TEXT("HEX"), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, rc.left + 10, rc.top + 140, 100, 25, hWnd, (HMENU)IDC_RADIO_HEX, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

	g_hStaticResult = CreateWindow(TEXT("static"), TEXT("Результат: 0"), WS_VISIBLE | WS_CHILD | SS_LEFT, rc.left + 180, rc.top + 10, 250, 25, hWnd, (HMENU)IDC_STATIC_RESULT, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

	Button_Enable(g_hRadioBin, FALSE);
	Button_Enable(g_hRadioThree, FALSE);
	Button_Enable(g_hRadioOct, FALSE);
	Button_Enable(g_hRadioHex, FALSE);

	//CheckRadioButton(g_hRadioBin, IDC_RADIO_BIN, IDC_RADIO_HEX, IDC_RADIO_BIN);
	//Button_SetCheck(g_hRadioBin, BM_SETCHECK);


	HANDLE  hFindFile;
	WIN32_FIND_DATA  fd;

	// находим первый файл
	hFindFile = FindFirstFile(TEXT("D:\\Projects\\OS_LABS\\x64\\Debug\\*.dll"), &fd);

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

		//TCHAR stringText[100];
		//sprintf_s(stringText, 100, TEXT("Файл найден - %s"), fd.cFileName);
		//MessageBox(hWnd, stringText, TEXT("Успех"), MB_OK);
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

// WM_LBUTTONDOWN
void  km_OnLButtonDown(HWND hWnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
}

// WM_RBUTTONDOWN
void  km_OnRButtonDown(HWND hWnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
}

// WM_ONPAINT
void km_OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(hWnd, &ps);
	RECT rc;
	GetClientRect(hWnd, &rc);

	//int x1, y1, x2, y2;
	//POINT pointtop, pointbottom;
	////Get The Coordinates of the Window.

	//pointtop = { rc.left,rc.top };
	//pointbottom = { rc.right, rc.bottom };

	////Break the Coordinates into four different variables.
	//x1 = pointtop.x;
	//y1 = pointtop.y;
	//x2 = pointbottom.x;
	//y2 = pointbottom.y;


	//HRGN region = CreateRoundRectRgn(x1, y1, x2, y2, 50, 50);
	//SetWindowRgn(hWnd, region, TRUE);

	//SetWindowPos(g_hEdit, HWND_TOP, rc.left, rc.top, rc.right, rc.bottom - 50, NULL);
	EndPaint(hWnd, &ps);
}

// WM_ONCLOSE
void km_OnClose(HWND hWnd)
{
	DestroyWindow(hWnd);
}

// WM_MENUSELECT
void km_OnMenuSelect(HWND hWnd, HMENU hmenu, int item, HMENU hmenuPopup, UINT flags)
{
}

// WM_DESTROY
void km_OnDestroy(HWND hWnd)
{
	//MessageBox(hWnd, g_lpszDestroyMessage, g_lpszDestroyTitle, MB_OK | MB_ICONEXCLAMATION);

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
	case IDM_FILE_EXIT:
	{
		DestroyWindow(hWnd);
	}
	break;
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

		//MessageBox(hWnd, buf, TEXT("Результат"), MB_OK);
		TCHAR result[200];
		wsprintf(result, TEXT("Результат: %s"), buf);

		Static_SetText(g_hStaticResult, result);

	}
	break;
	break;
	case IDM_HELP_ABOUT:
	{
		//DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_DIALOG1), hWnd, ModAboutDlgProc);
		DialogBox((HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), MAKEINTRESOURCE(IDD_DIALOG1), hWnd, (DLGPROC)ModAboutDlgProc);
	}
	break;
	default:
	{
		//MessageBox(hWnd, TEXT("Стандартная функция"), buff, MB_OK);
	}
	break;
	}
}

BOOL CALLBACK ModAboutDlgProc(HWND hDlg, UINT mes, WPARAM wParam, LPARAM lParam)
{
	switch (mes)
	{
	case WM_INITDIALOG:
	{
		TCHAR buff[200];
		GetDlgItemText(hDlg, IDC_STATIC1, buff, 200);
		//MessageBox(hDlg, buff, NULL, MB_OK);
		SYSTEMTIME st;
		GetLocalTime(&st);
		TCHAR buff1[200];
		wsprintf(buff1, TEXT("Текущая дата: %d.%d.%d и время %d:%d:%d \n "), st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute, st.wSecond);
		lstrcat(buff1, buff);
		SetDlgItemText(hDlg, IDC_STATIC1, buff1);
	}
	return TRUE;
	case WM_COMMAND:
	{
		int id = LOWORD(wParam);

		switch (id)
		{
		case IDOK:
			EndDialog(hDlg, IDOK);
		case IDCANCEL:
			EndDialog(hDlg, IDCANCEL);
		}
	}
	break;
	case WM_CLOSE:
	{
		EndDialog(hDlg, IDCANCEL);
	}
	return TRUE;
	}
	return FALSE;
}


