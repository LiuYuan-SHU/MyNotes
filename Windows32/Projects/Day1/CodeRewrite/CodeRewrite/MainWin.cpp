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
	// 创建窗口
	//window class
	WNDCLASS window;

	wchar_t windowClassName[] = L"Window Class Name";
	// class style : Horizontal Redraw | Vertical Redraw
	window.style = CS_HREDRAW | CS_VREDRAW;
	// long pointer function window proceed
	window.lpfnWndProc = WindowProc;
	// 额外字节分配
	window.cbClsExtra = 0;
	window.cbWndExtra = 0;
	// 当前程序实例句柄
	window.hInstance = hInstance;
	// 设置当前窗口的图标
	window.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(ICON_MAIN));
	// 设置当前窗口的鼠标指针
	window.hCursor = LoadCursor(NULL, IDC_CROSS);
	// 设置当前窗口的背景
	window.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
	// 设置菜单名称
	window.lpszMenuName = NULL;
	// 设置类名称
	window.lpszClassName = windowClassName;

	// 注册窗口
	if (!RegisterClass(&window))
	{
		MessageBox(NULL, L"注册窗口失败", L"错误", MB_OK);
		return -1;
	}

	// 创建窗口
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
		// 父窗口句柄
		NULL,
		// 菜单句柄
		NULL,
		// 窗口实例句柄
		hInstance,
		// long pointer parameter
		NULL
		);

	if (hWindow == NULL)
	{
		MessageBox(NULL, L"创建窗口失败", L"错误", MB_OK);
		return -1;
	}

	// 显示窗口
	// show window: show
	ShowWindow(hWindow, SW_SHOW);

	// 更新窗口
	UpdateWindow(hWindow);

	// 消息循环
	MSG message;
	while (GetMessage(&message, NULL, 0, 0))
	{
		// 转换虚拟键
		TranslateMessage(&message);
		// 将虚拟键发给窗口处理函数
		DispatchMessage(&message);
	}

	return 0;
}