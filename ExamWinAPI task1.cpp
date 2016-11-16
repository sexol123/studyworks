#include <Windows.h> 
#include <tchar.h> 
#include <time.h>

//Процедура обробки повідомлень 
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

int WINAPI WinMain(HINSTANCE hInstance, //Дескриптор поточного додатку 
	HINSTANCE Prev, //В сучасних додатках 0 
	LPSTR cmd, //Командний рядок 
	int mode) //Режим відображення вікна 
{
	srand(time(NULL));
	HWND hWnd; //Дескриптор головного вікна програми 
	MSG msg; //Структура для збереження повідомлень 
	WNDCLASS wc; //Клас вікна 

				 //Визначаємо клас вікна 
	wc.style = CS_HREDRAW | CS_VREDRAW; //Стиль вікна 
	wc.lpfnWndProc = MainWinProc; //Функція вікна 
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //Стандартна іконка 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); //Стандартний курсор 
	wc.lpszMenuName = NULL; //Немає меню 
	wc.lpszClassName = WinName; //Ім'я класу вікна 
	wc.cbClsExtra = 0; //Немає додаткових даних класу 
	wc.cbWndExtra = 0; //Немає додаткових даних вікна 
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); //Вікно білим кольором 

												   //Реєструємо головне вікно 
	if (!RegisterClass(&wc)) return false;

	//Створюємо головне вікно 
	hWnd = CreateWindow(WinName, //Ім'я класу вікна 
		_T("Арифметическое действие [Экзамен WinAPI]"), //Заголовок вікна 
		WS_OVERLAPPEDWINDOW, //Стиль вікна 
		310, // x 
		195, // y 
		440, // Width 
		295, // Height 
		HWND_DESKTOP, // Дескриптор батьківського вікна 
		NULL, // Немає меню 
		hInstance, // Дескриптор додатку 
		NULL); //Додаткової інформації немає 

	if (!hWnd) return false;

	//Відображаємо головне вікно 
	ShowWindow(hWnd, mode);
	//Якщо вікно містить елементи управління - оновлюємо їх 
	UpdateWindow(hWnd);

	//Цикл обробки повідомлень 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); //Функція трансляції кодів натиснутої клавіші 
		DispatchMessage(&msg); //Надсилає повідомленя функції MainWinProc() 
	}

	return msg.wParam;
}


LRESULT CALLBACK MainWinProc(HWND hw, UINT msg, WPARAM wp, LPARAM lp)
{
	//Обробник повідомлень 
	switch (msg)
	{
	case WM_CREATE:
	{
		hwListBox = CreateWindow(L"listbox", L"",
			WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_BORDER | LBS_NOTIFY | WS_VSCROLL,
			15, 15, 100, 200, hw, (HMENU)btnStart, hInst, NULL);

		hwRbSum = CreateWindow(L"button", L"Старт",
			WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON | BS_SOLID,
			15, 215, 100, 25, hw, (HMENU)btnStart, hInst, NULL);

		hwRbDob = CreateWindow(L"button", L"Сумма чисел",
			WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS | BS_AUTORADIOBUTTON,
			155, 35, 200, 25, hw, (HMENU)rbSumma, hInst, NULL);

		hwRbMid = CreateWindow(L"button", L"Произведение чисел",
			WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS | BS_AUTORADIOBUTTON,
			155, 55, 200, 25, hw, (HMENU)rbProizved, hInst, NULL);

		CreateWindow(L"button", L"Среднее арифметическое",
			WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS | BS_AUTORADIOBUTTON,
			155, 75, 200, 25, hw, (HMENU)rbSrAriphmethic, hInst, NULL);

		hwGroupBox = CreateWindow(L"button", L"Арифметическое действие",
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
	//Завершення програми 
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

		//Обробка повідомлень за замовчуванням 
	default:
		return DefWindowProc(hw, msg, wp, lp);
	}
	return 0;
}