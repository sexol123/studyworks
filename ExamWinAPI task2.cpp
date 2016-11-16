#include <Windows.h> 
#include <tchar.h> 

 
LRESULT CALLBACK MainWinProc(HWND hw, UINT msg, WPARAM wp, LPARAM lp);
TCHAR WinName[] = _T("SimpleWindow");
HINSTANCE hInst = NULL;
HANDLE himg;
HWND hwpictureBox = NULL;

enum Buttons {
	btnAdd,
	btnDel,
	comboBox,
	btnRnd
};

int index = 0;

HWND hwCbWindows = NULL;
HWND hwCb[1000];
int cb_i = 0;
HWND hwBn[1000];
int bn_i = 0;
HWND hwEd[1000];
int ed_i = 0;
HWND hwLb[1000];
int lb_i = 0;
HWND hwSt[1000];
int st_i = 0;

int WINAPI WinMain(HINSTANCE hInstance, 
	HINSTANCE Prev, 
	LPSTR cmd, 
	int mode) 
{
	HWND hWnd;  
	MSG msg; 
	WNDCLASS wc;  

				 
	wc.style = CS_HREDRAW | CS_VREDRAW;  
	wc.lpfnWndProc = MainWinProc;  
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);  
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);  
	wc.lpszMenuName = NULL;  
	wc.lpszClassName = WinName;  
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;  
	wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);  

												  
	if (!RegisterClass(&wc)) return false;

	 
	hWnd = CreateWindow(WinName,  
		_T("Экзамен WinAPI задание 2"), 
		WS_OVERLAPPEDWINDOW,  
		CW_USEDEFAULT,  
		CW_USEDEFAULT, 
		1000,  
		500,  
		HWND_DESKTOP,  
		NULL, 
		hInstance, 
		NULL);  

	if (!hWnd) return false;

	
	ShowWindow(hWnd, mode);
	
	UpdateWindow(hWnd);

	
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg); 
	}

	return msg.wParam;
}

LRESULT CALLBACK MainWinProc(HWND hw, UINT msg, WPARAM wp, LPARAM lp)
{
	
	switch (msg)
	{
	case WM_CREATE:
	{
		CreateWindow(L"button", L"Добавить",
			WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,
			15, 15, 90, 25, hw, (HMENU)btnAdd, hInst, NULL);

		CreateWindow(L"button", L"Удалить",
			WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,
			120, 15, 90, 25, hw, (HMENU)btnDel, hInst, NULL);

		hwCbWindows = CreateWindow(L"combobox", L"Категория",
			WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_BORDER | LBS_SORT | LBS_NOTIFY | WS_VSCROLL,
			15, 55, 200, 750, hw, (HMENU)comboBox, hInst, NULL);

		SendMessage(hwCbWindows, CB_ADDSTRING, NULL, (LPARAM)L"BUTTON");
		SendMessage(hwCbWindows, CB_ADDSTRING, NULL, (LPARAM)L"COMBOBOX");
		SendMessage(hwCbWindows, CB_ADDSTRING, NULL, (LPARAM)L"EDIT");
		SendMessage(hwCbWindows, CB_ADDSTRING, NULL, (LPARAM)L"LISTBOX");
		SendMessage(hwCbWindows, CB_ADDSTRING, NULL, (LPARAM)L"STATIC");
		SendMessage(hwCbWindows, CB_SETCURSEL, NULL, (LPARAM)L"BUTTON");
		
		return 0;
	}
	case WM_COMMAND:
	{
		switch (HIWORD(wp))
		{
		case BN_CLICKED:
		{
			switch (LOWORD(wp))
			{
			case btnAdd:
			{
				index = SendMessage(hwCbWindows, CB_GETCURSEL, NULL, NULL);
				switch (index) {
				case 0:
				{
					bn_i++;
					hwBn[bn_i] = CreateWindow(L"button", L"BUTTON",
						WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,
						50 + rand() % 800, 80 + rand() % 400, 20 + rand() % 180, 25 + rand() % 50, hw, (HMENU)btnRnd, hInst, NULL);
					return 0;
				}
				case 1:
				{
					cb_i++;
					hwCb[cb_i] =
						CreateWindow(L"combobox", L"",
							WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_BORDER | LBS_SORT | LBS_NOTIFY | WS_VSCROLL,
							50 + rand() % 800, 80 + rand() % 400, 20 + rand() % 180, 50, hw, NULL, hInst, NULL);
					return 0;
				}
				case 2:
				{
					ed_i++;
					hwEd[ed_i] = CreateWindow(L"edit", L"EDIT",
						WS_CHILD | WS_VISIBLE | BS_TEXT | WS_BORDER | ES_MULTILINE,
						50 + rand() % 800, 80 + rand() % 400, 20 + rand() % 180, 20 + rand() % 180, hw, NULL, hInst, NULL);
					return 0;
				}
				case 3:
				{
					lb_i++;
					hwLb[lb_i] = CreateWindow(L"listbox", L"LISTBOX",
						WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_BORDER | LBS_NOTIFY | WS_VSCROLL,
						50 + rand() % 800, 80 + rand() % 400, 20 + rand() % 180, 20 + rand() % 180, hw, NULL, hInst, NULL);
					return 0;
				}
				case 4:
				{
					st_i++;
					hwSt[st_i] = CreateWindow(L"static", L"STATIC",
						WS_CHILD | WS_VISIBLE | BS_TEXT | WS_BORDER,
						50 + rand() % 800, 80 + rand() % 400, 20 + rand() % 180, 20 + rand() % 180, hw, NULL, hInst, NULL);
					return 0;
				}
				default:
				{
					return 0;
				}

				}
				return 0;
			}
			case btnDel:
			{
				index = SendMessage(hwCbWindows, CB_GETCURSEL, NULL, NULL);
				switch (index) {
				case 0:
				{
					DestroyWindow(hwBn[bn_i]);
					if (bn_i>0)
						bn_i--;
					return 0;
				}
				case 1:
				{
					DestroyWindow(hwCb[cb_i]);
					if (cb_i>0)
						cb_i--;
					return 0;
				}
				case 2:
				{
					DestroyWindow(hwEd[ed_i]);
					if (ed_i>0)
						ed_i--;
					return 0;
				}
				case 3:
				{
					DestroyWindow(hwLb[lb_i]);
					if (lb_i>0)
						lb_i--;
					return 0;
				}
				case 4:
				{
					DestroyWindow(hwSt[st_i]);
					if (st_i>0)
						st_i--;
					return 0;
				}
				default:
				{
					return 0;
				}

				}
				return 0;
			}
			default:
			{
				return 0;
			}
			}
			return 0;
		}
		default:
		{
			return 0;
		}
		}
		return 0;
	}
	
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

		
	default:
		return DefWindowProc(hw, msg, wp, lp);
	}
	return 0;
}