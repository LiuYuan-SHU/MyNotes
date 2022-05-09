#include <Windows.h>
#include <Windowsx.h>
#include "resource.h"

// �Զ�����Ϣһ��Ҫ��1024���ϵģ����µĶ��Ѿ�������ϵͳʹ����
/*
// NOTE: All Message Numbers below 0x0400 are RESERVED.
// 
// Private Window Messages Start Here:
#define WM_USER                         0x0400
*/
#define UM_TEST	WM_USER + 1		// �Զ��������Ϣ

// window handle / message / width parameter / length parameter
LRESULT CALLBACK WindowProc(HWND hWind, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// NEW Code
	wchar_t szMsg[100];
	// sprintf();
	wsprintf(szMsg, L"hWindow: %x\tuMsg: %-10d\twParam: %-10d\tlParam: %-10d\n", hWind, uMsg, wParam, lParam);

	OutputDebugString(szMsg);

	switch (uMsg)
	{
	case WM_CREATE:
	{
					  // ���ڿͻ���������Ϣ���������ǱȽ����һ����Ϣ
					  // ��ʱ�����Ѿ��������ˣ�ֻ����û����ʾ����
					  // ֻҪʹ�� CreateWindow ���� CreateWindowEx ���ͷ��������Ϣ
					  // ����һ���������е���Ϣ������ҪGetMessage�����л�ȡ
					  // wParam��ʹ��
					  // lParam��һ���ṹ��ָ��

					  // ����һ��ָ����Ϊcs�Ľṹ���ָ��
					  //LPCREATESTRUCT cs;
					  // ��һ������ �������ڵ�ʱ�򴫵ݵ���Ϣ��
					  // ����ֲ����Ƶ
					  LPCREATESTRUCT lpcs = (LPCREATESTRUCT)lParam;

					  // MessageBox(NULL, L"Window Create", L"��ʾ", MB_OK);
					  // ���ñ���
					  SetWindowText(hWind, L"�ٿ�����");
					  break;
	}

	case UM_TEST:
	{
					MessageBox(hWind, L"�û��Զ�����Ϣ", L"��ʾ", MB_OK);
					break;
	}

	case WM_LBUTTONDOWN:
	{
						   SendMessage(hWind, UM_TEST, 10, 10);
							// HWND hNodePad = FindWindow(L"NotePad", L"�ޱ��� - ���±�");
							// if (hNodePad)
							// {
							//PostMessage(hNodePad, WM_CLOSE, 0, 0);
							// }
						   // ������Ϣ
						   // SendMessage
						   // PostMessage

						   // ����WM_CLOSE��Ϣ
						   // SendMessage(hWind, WM_CLOSE, 0, 0);
						   // PostMessage(hWind, WM_CLOSE, 0, 0);

						   // �������̰�����Ϣ
						   // SendMessage(hWind, WM_KEYDOWN, 0x41, 0);

		// ������<Windowsx>ͷ�ļ��У�����������ĺ�������
		// int x = GET_X_LPARAM(lParam);
		// int y = GET_Y_LPARAM(lParam);

		/*int x = LOWORD(lParam);
		int y = HIWORD(lParam);

		wchar_t szText[100] = { 0 };
		wsprintf(szText, L"��ǰ�������: (%d, %d)", x, y);
		if (wParam & MK_CONTROL)
		{
			wcscat(szText, L"ctrl����");
		}
		if (wParam & MK_SHIFT)
		{
			wcscat(szText, L"shift����");
		}
		if (wParam & MK_LBUTTON)
		{
			wcscat(szText, L"�������");
		}
		if (wParam & MK_MBUTTON)
		{
			wcscat(szText, L"�м�����");
		}
		if (wParam & MK_RBUTTON)
		{
			wcscat(szText, L"�Ҽ�����");
		}
		SetWindowText(hWind, szText);*/
		break;
	}
	case WM_MOUSEMOVE:
	{
						 int x = LOWORD(lParam);
						 int y = HIWORD(lParam);

						 wchar_t szText[100] = { 0 };
						 wsprintf(szText, L"��ǰ�������: (%d, %d)", x, y);
						 SetWindowText(hWind, szText);
						 break;
	}
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_RETURN:
			   MessageBox(hWind, L"�����˻س�", L"��ʾ", MB_OK);
			   break;
		case VK_SPACE:
			   MessageBox(hWind, L"�����˿ո�", L"��ʾ", MB_OK);
			   break; 
		case VK_ESCAPE:
			   MessageBox(hWind, L"������Esc", L"��ʾ", MB_OK);
			   break;
		case VK_F1:
			   MessageBox(hWind, L"������F1", L"��ʾ", MB_OK);
			   break;
		case 0x41:
		{
					 wchar_t szText[] = L"����A";
					 SetWindowText(hWind, szText);
					 // �����λ��1����ô���£�����̧��
					 // �����λ��1����ô������Ѿ��������������д��
					 short s = GetKeyState(VK_CONTROL);
					 if (s < 0)
					 {
						 MessageBox(hWind, L"Ctrl + A", L"��ʾ", MB_OK);
					 }

					 break;
		}
		case VK_NUMPAD0:
			   MessageBox(hWind, L"������С����0", L"��ʾ", MB_OK);
			   break;
		case 0x30:
			   MessageBox(hWind, L"��������ĸ�Ϸ�0", L"��ʾ", MB_OK);
			   break;
		case VK_F3:
			   if (lParam >> 29 & 1)
			   {
				   MessageBox(hWind, L"������Alt + F3", L"��ʾ", MB_OK);
			   }
			   break;
		}
		break;
	}
	case WM_CHAR:
	{
					wchar_t szText[100];
					wsprintf(szText, L"���µļ��� %c", (char)wParam);
					SetWindowText(hWind, szText);
					break;
	}
	case WM_SIZE:
	{
					wchar_t szText[] = L"���ڴ�С�ı�";
					SetWindowText(hWind, szText);
					break;
	}
	case WM_PAINT:
	{
					 // ��ʼ��ͼ
					 PAINTSTRUCT ps;
					 HDC dc = BeginPaint(hWind, &ps);

					 // ��ͼ����
					 // �ı���
					 Rectangle(dc, 20, 20, 100, 100);
					 // Բ�κ���Բ��
					 Ellipse(dc, 30, 30, 120, 150);
					 // ��ӡ��
					 wchar_t szText[100] = L"������";
					 TextOut(dc, 300, 300, szText, wcslen(szText));

					 // ������ͼ
					 EndPaint(hWind, &ps);

					 break;
	}
		// window message: close
	case WM_CLOSE:
		// wParam��lParam��ʹ��
		/*DestroyWindow(hWind);*/
		if (IDYES == MessageBox(NULL, L"ȷ��Ҫ�رմ�����", L"��ʾ", MB_YESNO))
		{
			DestroyWindow(hWind);
		}
		else
		{
			ShowWindow(hWind, SW_MINIMIZE);
			// �����break / ���ǲ��ţ���ô�ͻᵽ���ڵ�Ĭ�ϴ�����
			// ��������Ҳ��ر�
			// Ϊ�˲����ô��ڵ�Ĭ�Ϻ���������Ҫ�Լ����
			// return 1;		// ����ҪĬ�Ϻ������
			return 0;			// �������û�н������Ĭ�Ϻ������
		}
		break;
		// window message: destroy
	case WM_DESTROY:
		// ������
		// wParam��lParam��ʹ��
		PostQuitMessage(0);
		break;
	}

	// default window proceed
	return DefWindowProc(hWind, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ��������
	//window class
	WNDCLASS window;

	wchar_t windowClassName[] = L"Window Class Name";
	// class style : Horizontal Redraw | Vertical Redraw
	window.style = CS_HREDRAW | CS_VREDRAW;
	// long pointer function window proceed
	window.lpfnWndProc = WindowProc;
	// �����ֽڷ���
	window.cbClsExtra = 0;
	window.cbWndExtra = 0;
	// ��ǰ����ʵ�����
	window.hInstance = hInstance;
	// ���õ�ǰ���ڵ�ͼ��
	window.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(ICON_MAIN));
	// ���õ�ǰ���ڵ����ָ��
	window.hCursor = LoadCursor(NULL, IDC_CROSS);
	// ���õ�ǰ���ڵı���
	window.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
	// ���ò˵�����
	window.lpszMenuName = NULL;
	// ����������
	window.lpszClassName = windowClassName;

	// ע�ᴰ��
	if (!RegisterClass(&window))
	{
		MessageBox(NULL, L"ע�ᴰ��ʧ��", L"����", MB_OK);
		return -1;
	}

	// ��������
	wchar_t className[] = L"Class Name";
	wchar_t windowName[] = L"Window Name";

	HWND hWindow = CreateWindow(
		windowClassName,
		windowName,
		// WS_CAPTION		The window has a title bar(includes the WS_BORDER style).
		// WS_SYSMENU		The window has a window menu on its title bar. The WS_CAPTION style must also be specified.
		// WS_MAXIMIZEBOX	The window has a maximize button. Cannot be combined with the WS_EX_CONTEXTHELP style. The WS_SYSMENU style must also be specified.
		// WS_MINIMIZEBOX	The window has a minimize button. Cannot be combined with the WS_EX_CONTEXTHELP style. The WS_SYSMENU style must also be specified.
		WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX,
		200,
		200,
		800,
		600,
		// �����ھ��
		NULL,
		// �˵����
		NULL,
		// ����ʵ�����
		hInstance,
		// long pointer parameter
		NULL
		);

	if (hWindow == NULL)
	{
		MessageBox(NULL, L"��������ʧ��", L"����", MB_OK);
		return -1;
	}

	// ��ʾ����
	// show window: show
	ShowWindow(hWindow, SW_SHOW);

	// ���´���
	UpdateWindow(hWindow);

	// ��Ϣѭ��
	MSG message;
	while (GetMessage(&message, NULL, 0, 0))
	{
		// ת�������
		TranslateMessage(&message);
		// ��������������ڴ�����
		DispatchMessage(&message);
	}

	return 0;
}