#include "LB_02.h"
#include "stdio.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpszCmdLine, int nCmdShow)
{
	MSG msg;
	HWND hWnd;

	if (!Register(hInstance)) return FALSE;

	hWnd = Create(hInstance, nCmdShow);

	if (hWnd == NULL) return FALSE;

	g_hwndDlg = (HWND)0;
	g_hInst = hInstance;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateMDISysAccel(g_hMDIClientWnd, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		HANDLE_MSG(hWnd, WM_COMMAND, km_OnCommand);				// Комманды
		HANDLE_MSG(hWnd, WM_CLOSE, km_OnClose);					// Закрытие окна
		HANDLE_MSG(hWnd, WM_SIZE, km_OnSize);					// Закрытие окна
		HANDLE_MSG(hWnd, WM_CREATE, km_OnCreate);				// Создание окна
		//HANDLE_MSG(hWnd, WM_PAINT, km_OnPaint);					// Перерысовывание окна
		HANDLE_MSG(hWnd, WM_DESTROY, km_OnDestroy);				// Разружение окна
	}

	return	DefFrameProc(hWnd, g_hMDIClientWnd, msg, wParam, lParam);
}

LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_COMMAND, km_OnChildCommand);				// Комманды
		//HANDLE_MSG(hWnd, WM_CLOSE, km_OnChildClose);					// Закрытие окна
		HANDLE_MSG(hWnd, WM_CREATE, km_OnChildCreate);				// Создание окна
		HANDLE_MSG(hWnd, WM_MDIACTIVATE, km_OnChildActivate);		// Активация окна
		HANDLE_MSG(hWnd, WM_SIZE, km_OnChildSize);
		HANDLE_MSG(hWnd, WM_SETFOCUS, km_OnChildSetFocus);			// получение фокуса окна
		//HANDLE_MSG(hWnd, WM_DESTROY, km_OnDestroy);				// Разружение окна
	}
	return DefMDIChildProc(hWnd, message, wParam, lParam);
}


BOOL Register(HINSTANCE hInst)
{
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MainWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_3DSHADOW + 1);
	wc.lpszClassName = g_lpszClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, TEXT("Ошибка регистрации класса"),
			TEXT("Ошибка"), MB_OK | MB_ICONERROR);
		return FALSE;
	}


	wc.lpfnWndProc = ChildWndProc;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_lpszChildClassName;
	wc.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, TEXT("Ошибка регистрации MDI класса"),
			TEXT("Ошибка"), MB_OK | MB_ICONERROR);
		return FALSE;
	}


	return TRUE;
}

HWND Create(HINSTANCE hInstance, int nCmdShow)
{
	DWORD Stl;
	Stl = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN;

	g_lpszMainMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));


	HWND hWnd = CreateWindowEx(WS_EX_APPWINDOW, g_lpszClassName,
		"MDI File Editor", WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		0, g_lpszMainMenu, hInstance, NULL);

	if (!hWnd)
	{
		MessageBox(NULL, TEXT("Окно не создано"),
			TEXT("Ошибка"), MB_OK | MB_ICONERROR);
		return NULL;
	}

	g_hMainWnd = hWnd;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}



// WM_CREATE
BOOL km_OnCreate(HWND hWnd, LPCREATESTRUCT lpszCreateStruct)
{
	g_lpszFileMenu = GetSubMenu(g_lpszMainMenu, 0);
	g_lpszViewMenu = GetSubMenu(g_lpszMainMenu, 1);

	////////////////////////////////////////
	CLIENTCREATESTRUCT ccs;
	memset(&ccs, 0, sizeof(CLIENTCREATESTRUCT));

	// Find window menu where children will be listed
	ccs.hWindowMenu = g_lpszViewMenu;
	ccs.idFirstChild = ID_MDI_FIRSTCHILD;
	g_hMDIClientWnd = CreateWindowEx(WS_EX_CLIENTEDGE, "mdiclient", NULL,
		WS_CHILD | WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		hWnd, (HMENU)ID_MDI_CLIENT, g_hInst, (LPVOID)&ccs);

	if (!g_hMDIClientWnd)
		return FALSE;

	ShowWindow(g_hMDIClientWnd, SW_SHOW);


	return TRUE;
}

// WM_SIZE
void km_OnSize(HWND hWnd, UINT wSizeType, SHORT cx, SHORT cy)
{
	RECT rectClient;
	UINT uClientAlreaHeight;

	GetClientRect(hWnd, &rectClient);
	uClientAlreaHeight = rectClient.bottom;

	MoveWindow(g_hMDIClientWnd, 0, 0, rectClient.right, uClientAlreaHeight, TRUE);

	//DefFrameProc(hWnd, g_hMDIClientWnd, 0, (WPARAM)wSizeType, MAKELPARAM(cx, cy));
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
	case IDM_FILE_EXIT:
	{
		MDICREATESTRUCT mcs;
		HWND hChild;

		mcs.szTitle = "[Untitled]";
		mcs.szClass = g_lpszChildClassName;
		mcs.hOwner = g_hInst;
		mcs.x = mcs.cx = CW_USEDEFAULT;
		mcs.y = mcs.cy = CW_USEDEFAULT;
		mcs.style = MDIS_ALLCHILDSTYLES;

		hChild = (HWND)SendMessage(g_hMDIClientWnd, WM_MDICREATE,
			0, (LPARAM)&mcs);
		if (!hChild)
		{
			MessageBox(hWnd, "MDI Child creation failed.", "Oh Oh...",
				MB_ICONEXCLAMATION | MB_OK);
		}

	}
	break;
	case IDM_HELP_ABOUT:
	{
		DialogBox((HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), MAKEINTRESOURCE(IDD_DIALOG1), hWnd, (DLGPROC)ModAboutDlgProc);
	}
	break;
	default:
	{
		if (id >= ID_MDI_FIRSTCHILD) {
			DefFrameProc(hWnd, g_hMDIClientWnd, 0, (WPARAM)hwndCtl, (LPARAM)id);
		}
		else {
			HWND hChild;
			hChild = (HWND)SendMessage(g_hMDIClientWnd, WM_MDIGETACTIVE, 0, 0);
			if (hChild) {
				SendMessage(hChild, WM_COMMAND, (WPARAM)hwndCtl, (LPARAM)id);
			}
		}
	}
	break;
	}
}


////////////////////////////////////////
//////////////////////////////////////////
// WM_CREATE
BOOL km_OnChildCreate(HWND hWnd, LPCREATESTRUCT lpszCreateStruct)
{
	RECT rc;
	GetClientRect(hWnd, &rc);


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

	} while (FindNextFile(hFindFile, &fd));

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

// WM_MDIACTIVATE
BOOL km_OnChildActivate(HWND hWnd, BOOL bActive, HWND hWndActive, HWND hWndDeactive)
{
	HMENU hMenu, hFileMenu;
	BOOL EnableFlag;
	char szFileName[MAX_PATH];

	hMenu = GetMenu(g_hMainWnd);
	if (hWnd == hWndActive) {      //being activated
		EnableFlag = TRUE;
	}
	else {
		EnableFlag = FALSE;    //being de-activated
	}

	//DrawMenuBar(g_hMainWnd);

	return TRUE;
}

// WM_SIZE 
void km_OnChildSize(HWND hWnd, UINT wSizeType, SHORT cx, SHORT cy)
{
	if (wSizeType != SIZE_MINIMIZED)
		MoveWindow(GetDlgItem(hWnd, IDC_CHILD_EDIT), 0, 0,cx,cy, TRUE);

	DefMDIChildProc(hWnd, WM_SIZE, (WPARAM)wSizeType, MAKELPARAM(cx, cy));
}

// WM_ONPAINT
void km_OnChildPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(hWnd, &ps);
	RECT rc;
	GetClientRect(hWnd, &rc);

	EndPaint(hWnd, &ps);
}

// WM_ONCLOSE
void km_OnChildClose(HWND hWnd)
{
	DestroyWindow(hWnd);
}

// WM_DESTROY
void km_OnChildDestroy(HWND hWnd)
{
	PostQuitMessage(0);
}

// WM_COMMAND
void km_OnChildCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
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

// WM_SETFOCUS
void km_OnChildSetFocus(HWND hwnd, HWND hWndOldFocus)
{
	SetFocus(GetDlgItem(hwnd, IDC_CHILD_EDIT));
}



BOOL CALLBACK ModAboutDlgProc(HWND hDlg, UINT mes, WPARAM wParam, LPARAM lParam)
{
	switch (mes)
	{
	case WM_INITDIALOG:
	{
		TCHAR buff[200];
		GetDlgItemText(hDlg, IDC_STATIC1, buff, 200);
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


