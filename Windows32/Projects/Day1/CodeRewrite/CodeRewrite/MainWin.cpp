#include <Windows.h>
#include "resource.h"

// window handle / message / width parameter / length parameter
LRESULT CALLBACK WindowProc(HWND hWind, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		// window message: close
	case WM_CLOSE:
		DestroyWindow(hWind);
		break;
		// window message: destroy
	case WM_DESTROY:
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