#include <windows.h>
#include <commctrl.h>

#define CM_WINDOW_TILEVERT	9080
#define CM_WINDOW_TILEHORZ	9082
#define CM_WINDOW_ARRANGE	9081
#define CM_WINDOW_TILE	9080
#define CM_WINDOW_CASCADE	9076
#define CM_EDIT_PASTE	9079
#define CM_EDIT_COPY	9078
#define CM_EDIT_CUT	9077
#define CM_EDIT_REDO	9076
#define CM_EDIT_UNDO	9075
#define CM_FILE_SAVEAS	9074
#define CM_FILE_SAVE	9073
#define CM_FILE_OPEN	9072
#define CM_HELP_ABOUT	9072
#define CM_FILE_EXIT	9071
#define CM_FILE_NEW	9070



#define ID_MDI_CLIENT      4999
#define ID_MDI_FIRSTCHILD  50000

#define IDC_CHILD_EDIT      2000

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK MDIChildWndProc(HWND hwnd, UINT Message, WPARAM wParam,
	LPARAM lParam);

char g_szAppName[] = "MyMDIWindow";
char g_szChild[] = "MyMDIChild";
HINSTANCE g_hInst;
HWND g_hMDIClient;
HWND g_hMainWindow;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPTSTR lpszCmdParam, int nCmdShow)
{
	MSG  Msg;
	WNDCLASSEX WndClassEx;

	g_hInst = hInstance;

	WndClassEx.cbSize = sizeof(WNDCLASSEX);
	WndClassEx.style = CS_HREDRAW | CS_VREDRAW;
	WndClassEx.lpfnWndProc = WndProc;
	WndClassEx.cbClsExtra = 0;
	WndClassEx.cbWndExtra = 0;
	WndClassEx.hInstance = hInstance;
	WndClassEx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClassEx.hbrBackground = (HBRUSH)(COLOR_3DSHADOW + 1);
	WndClassEx.lpszMenuName = "MAIN";
	WndClassEx.lpszClassName = g_szAppName;
	WndClassEx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&WndClassEx))
	{
		MessageBox(0, "Could Not Register Window", "Oh Oh...",
			MB_ICONEXCLAMATION | MB_OK);
		return -1;
	}

	WndClassEx.lpfnWndProc = MDIChildWndProc;
	WndClassEx.lpszMenuName = NULL;
	WndClassEx.lpszClassName = g_szChild;
	WndClassEx.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);

	if (!RegisterClassEx(&WndClassEx))
	{
		MessageBox(0, "Could Not Register Child Window", "Oh Oh...",
			MB_ICONEXCLAMATION | MB_OK);
		return -1;
	}

	g_hMainWindow = CreateWindowEx(WS_EX_APPWINDOW, g_szAppName,
		"MDI File Editor", WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		0, 0, hInstance, NULL);

	if (g_hMainWindow == NULL) {
		MessageBox(0, "No Window", "Oh Oh...", MB_ICONEXCLAMATION | MB_OK);
		return -1;
	}

	ShowWindow(g_hMainWindow, nCmdShow);
	UpdateWindow(g_hMainWindow);

	while (GetMessage(&Msg, NULL, 0, 0))
	{
		if (!TranslateMDISysAccel(g_hMDIClient, &Msg))
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
	}
	return (int)Msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	case WM_CREATE:
	{
		CLIENTCREATESTRUCT ccs;
		int iStatusWidths[] = { 200, 300, -1 };

		// Find window menu where children will be listed
		ccs.hWindowMenu = GetSubMenu(GetMenu(hwnd), 2);
		ccs.idFirstChild = ID_MDI_FIRSTCHILD;
		g_hMDIClient = CreateWindowEx(WS_EX_CLIENTEDGE, "mdiclient", NULL,
			WS_CHILD | WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			hwnd, (HMENU)ID_MDI_CLIENT, g_hInst, (LPVOID)&ccs);
		ShowWindow(g_hMDIClient, SW_SHOW);

		return 0;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case CM_FILE_EXIT:
			PostMessage(hwnd, WM_CLOSE, 0, 0);
			break;
		case CM_FILE_NEW:
		{
			MDICREATESTRUCT mcs;
			HWND hChild;

			mcs.szTitle = "[Untitled]";
			mcs.szClass = g_szChild;
			mcs.hOwner = g_hInst;
			mcs.x = mcs.cx = CW_USEDEFAULT;
			mcs.y = mcs.cy = CW_USEDEFAULT;
			mcs.style = MDIS_ALLCHILDSTYLES;

			hChild = (HWND)SendMessage(g_hMDIClient, WM_MDICREATE,
				0, (LPARAM)&mcs);
			if (!hChild)
			{
				MessageBox(hwnd, "MDI Child creation failed.", "Oh Oh...",
					MB_ICONEXCLAMATION | MB_OK);
			}
		}
		break;
		case CM_WINDOW_TILEHORZ:
			PostMessage(g_hMDIClient, WM_MDITILE, MDITILE_HORIZONTAL, 0);
			break;
		case CM_WINDOW_TILEVERT:
			PostMessage(g_hMDIClient, WM_MDITILE, MDITILE_VERTICAL, 0);
			break;
		case CM_WINDOW_CASCADE:
			PostMessage(g_hMDIClient, WM_MDICASCADE, 0, 0);
			break;
		case CM_WINDOW_ARRANGE:
			PostMessage(g_hMDIClient, WM_MDIICONARRANGE, 0, 0);
			break;
		default:
		{
			if (LOWORD(wParam) >= ID_MDI_FIRSTCHILD) {
				DefFrameProc(hwnd, g_hMDIClient, Message, wParam, lParam);

			}
			else {
				HWND hChild;
				hChild = (HWND)SendMessage(g_hMDIClient, WM_MDIGETACTIVE, 0, 0);
				if (hChild) {
					SendMessage(hChild, WM_COMMAND, wParam, lParam);
				}
			}
		}
		}
	}
	break;
	case WM_SIZE:
	{
		RECT rectClient;
		UINT uClientAlreaHeight;

		GetClientRect(hwnd, &rectClient);
		uClientAlreaHeight = rectClient.bottom;

		MoveWindow(g_hMDIClient, 0, 0, rectClient.right, uClientAlreaHeight, TRUE);
	}
	break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefFrameProc(hwnd, g_hMDIClient, Message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK MDIChildWndProc(HWND hwnd, UINT Message, WPARAM wParam,
	LPARAM lParam)
{
	switch (Message)
	{
	case WM_CREATE:
	{
		char szFileName[MAX_PATH];
		//HWND hEdit;

		//hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "",
		//	WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | ES_MULTILINE |
		//	ES_WANTRETURN,
		//	CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		//	hwnd, (HMENU)IDC_CHILD_EDIT, g_hInst, NULL);

		//SendMessage(hEdit, WM_SETFONT,
		//	(WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(TRUE, 0));

		GetWindowText(hwnd, szFileName, MAX_PATH);
	}
	break;
	case WM_SIZE:
		//if (wParam != SIZE_MINIMIZED)
		//	MoveWindow(GetDlgItem(hwnd, IDC_CHILD_EDIT), 0, 0, LOWORD(lParam),
		//		HIWORD(lParam), TRUE);
		break;
	case WM_MDIACTIVATE:
	{
		HMENU hMenu, hFileMenu;
		BOOL EnableFlag;
		char szFileName[MAX_PATH];

		hMenu = GetMenu(g_hMainWindow);
		if (hwnd == (HWND)lParam) {      //being activated
			EnableFlag = TRUE;
		}
		else {
			EnableFlag = FALSE;    //being de-activated
		}
		EnableMenuItem(hMenu, 1, MF_BYPOSITION | (EnableFlag ? MF_ENABLED : MF_GRAYED));
		EnableMenuItem(hMenu, 2, MF_BYPOSITION | (EnableFlag ? MF_ENABLED : MF_GRAYED));

		hFileMenu = GetSubMenu(hMenu, 0);
		EnableMenuItem(hFileMenu, CM_FILE_SAVE, MF_BYCOMMAND | (EnableFlag ? MF_ENABLED : MF_GRAYED));
		EnableMenuItem(hFileMenu, CM_FILE_SAVEAS, MF_BYCOMMAND | (EnableFlag ? MF_ENABLED : MF_GRAYED));

		DrawMenuBar(g_hMainWindow);

		GetWindowText(hwnd, szFileName, MAX_PATH);
	}
	break;
	case WM_SETFOCUS:
		//SetFocus(GetDlgItem(hwnd, IDC_CHILD_EDIT));
		break;
	}
	return DefMDIChildProc(hwnd, Message, wParam, lParam);
}

