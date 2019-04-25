#include "LB_04_GUI.h"


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
		350,
		200,
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

	g_hStaticResult = CreateWindow(TEXT("static"), TEXT("Результат: 0"), WS_VISIBLE | WS_CHILD | SS_LEFT, rc.left + 10, rc.top + 75, 250, 25, hWnd, (HMENU)IDC_STATIC_RESULT, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

	g_hCheckBox = CreateWindow(TEXT("button"),TEXT("Показывать окно консоли"), WS_VISIBLE | WS_CHILD | BS_CHECKBOX, rc.left + 10, rc.top + 110, 200, 25, hWnd, (HMENU)IDC_CHECKBOX, (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
	

	return(TRUE);
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

	switch (id)
	{
	case IDC_BUTTON_MAIN:
	{
		TCHAR buf[30];

		/*----Запись исходного числа из Edit в файл----*/
		Edit_GetText(g_hEdit, buf, 30);
		std::ofstream SetSource("in.txt");
		SetSource.write(buf, 30);
		SetSource.close();

		/*----Запуск и ожидание консольного приложения----*/
		
			STARTUPINFO ConsStartStruct;
			CreateProcess(TEXT("LB_04_CLI.exe"),NULL,);

			GetExitCodeProcess(NULL, NULL);
			



		
		/*----Чтение результата из файла и передача в Edit----*/
		std::ifstream GetResult("out.txt");
		if (!GetResult.is_open())
		{
			MessageBoxA(hWnd, TEXT("Нет файла с результатом!"), TEXT("Ошибка!"), MB_OK);
		}
		GetResult >> buf;
		Static_SetText(g_hStaticResult, buf);
		
	}
	break;
	case IDC_CHECKBOX:	
	{
		BOOL g_Checked = IsDlgButtonChecked(hWnd, IDC_CHECKBOX);
		if (g_Checked) {
			CheckDlgButton(hWnd, IDC_CHECKBOX, BST_UNCHECKED);
		}
		else {
			CheckDlgButton(hWnd, IDC_CHECKBOX, BST_CHECKED);
		}
	}
	break;
	default:
	{
		//MessageBox(hWnd, TEXT("Стандартная функция"), buff, MB_OK);
	}
	break;
	}
}


