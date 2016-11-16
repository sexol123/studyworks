#include <Windows.h> 
#include <tchar.h> 
#include <time.h>

//��������� ������� ���������� 
LRESULT CALLBACK MainWinProc(HWND hw, UINT msg, WPARAM wp, LPARAM lp);
TCHAR WinName[] = _T("Ariph");
HINSTANCE hInst = NULL;
HANDLE himg;
HWND hwpictureBox = NULL;
long long int sum = 0;
long long int dob = 1;
float mid;
bool isempty = true;

enum Buttons
{
	rbSumma,
	rbProizved,
	rbSrAriphmethic,
	btnStart
};

HWND hwRbSum = NULL;
HWND hwRbDob = NULL;
HWND hwRbMid = NULL;
HWND hwListBox = NULL;
HWND hwGroupBox = NULL;
HWND hwTextBox = NULL;

int WINAPI WinMain(HINSTANCE hInstance, //���������� ��������� ������� 
	HINSTANCE Prev, //� �������� �������� 0 
	LPSTR cmd, //��������� ����� 
	int mode) //����� ����������� ���� 
{
	srand(time(NULL));
	HWND hWnd; //���������� ��������� ���� �������� 
	MSG msg; //��������� ��� ���������� ���������� 
	WNDCLASS wc; //���� ���� 

				 //��������� ���� ���� 
	wc.style = CS_HREDRAW | CS_VREDRAW; //����� ���� 
	wc.lpfnWndProc = MainWinProc; //������� ���� 
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //���������� ������ 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); //����������� ������ 
	wc.lpszMenuName = NULL; //���� ���� 
	wc.lpszClassName = WinName; //��'� ����� ���� 
	wc.cbClsExtra = 0; //���� ���������� ����� ����� 
	wc.cbWndExtra = 0; //���� ���������� ����� ���� 
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); //³��� ���� �������� 

												   //�������� ������� ���� 
	if (!RegisterClass(&wc)) return false;

	//��������� ������� ���� 
	hWnd = CreateWindow(WinName, //��'� ����� ���� 
		_T("�������������� �������� [������� WinAPI]"), //��������� ���� 
		WS_OVERLAPPEDWINDOW, //����� ���� 
		310, // x 
		195, // y 
		440, // Width 
		295, // Height 
		HWND_DESKTOP, // ���������� ������������ ���� 
		NULL, // ���� ���� 
		hInstance, // ���������� ������� 
		NULL); //��������� ���������� ���� 

	if (!hWnd) return false;

	//³��������� ������� ���� 
	ShowWindow(hWnd, mode);
	//���� ���� ������ �������� ��������� - ��������� �� 
	UpdateWindow(hWnd);

	//���� ������� ���������� 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); //������� ���������� ���� ��������� ������ 
		DispatchMessage(&msg); //������� ���������� ������� MainWinProc() 
	}

	return msg.wParam;
}


LRESULT CALLBACK MainWinProc(HWND hw, UINT msg, WPARAM wp, LPARAM lp)
{
	//�������� ���������� 
	switch (msg)
	{
	case WM_CREATE:
	{
		hwListBox = CreateWindow(L"listbox", L"",
			WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_BORDER | LBS_NOTIFY | WS_VSCROLL,
			15, 15, 100, 200, hw, (HMENU)btnStart, hInst, NULL);

		hwRbSum = CreateWindow(L"button", L"�����",
			WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON | BS_SOLID,
			15, 215, 100, 25, hw, (HMENU)btnStart, hInst, NULL);

		hwRbDob = CreateWindow(L"button", L"����� �����",
			WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS | BS_AUTORADIOBUTTON,
			155, 35, 200, 25, hw, (HMENU)rbSumma, hInst, NULL);

		hwRbMid = CreateWindow(L"button", L"������������ �����",
			WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS | BS_AUTORADIOBUTTON,
			155, 55, 200, 25, hw, (HMENU)rbProizved, hInst, NULL);

		CreateWindow(L"button", L"������� ��������������",
			WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS | BS_AUTORADIOBUTTON,
			155, 75, 200, 25, hw, (HMENU)rbSrAriphmethic, hInst, NULL);

		hwGroupBox = CreateWindow(L"button", L"�������������� ��������",
			WS_VISIBLE | WS_CHILD | BS_GROUPBOX | WS_GROUP,
			135, 15, 240, 100, hw, NULL, hInst, NULL);

		hwTextBox = CreateWindow(L"edit", L"",
			WS_CHILD | WS_VISIBLE | BS_TEXT | WS_BORDER | ES_MULTILINE,
			135, 125, 200, 50, hw, NULL, hInst, NULL);

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
			case btnStart:
			{
				sum = 0;
				dob = 1;
				int num[20];
				wchar_t text[20];
				for (int i = 0; i < 20; i++) {
					do {
						num[i] = -10 + rand() % 20;
					} while (num[i]
						== 0);

					wsprintf(text, L"%i", num[i]);

					SendMessage(hwListBox, LB_ADDSTRING, (WPARAM)text, (LPARAM)text);
					sum += num[i];
					dob *= num[i];
				}

				mid = (float)sum / 20;
				return 0;
			}

			case rbSumma: {

				wchar_t text[20];
				wsprintf(text, L"%i", sum);
				SetWindowText(hwTextBox, text);
				return 0;
			}

			case rbProizved: {
				wchar_t text[20];
				wsprintf(text, L"%i", dob);
				SetWindowText(hwTextBox, text);
				return 0;
			}

			case rbSrAriphmethic: {
				wchar_t text[20];
				swprintf_s(text, L"%f", mid);
				SetWindowText(hwTextBox, text);
				return 0;
			}
			default:
				return 0;
			}
			return 0;
		}
		default:
			return 0;
		}
		return 0;
	}
	//���������� �������� 
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

		//������� ���������� �� ������������� 
	default:
		return DefWindowProc(hw, msg, wp, lp);
	}
	return 0;
}