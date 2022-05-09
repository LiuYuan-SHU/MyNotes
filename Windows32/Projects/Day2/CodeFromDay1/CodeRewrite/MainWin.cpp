#include <Windows.h>
#include <Windowsx.h>
#include "resource.h"

// 自定义消息一定要是1024以上的，以下的都已经被操作系统使用了
/*
// NOTE: All Message Numbers below 0x0400 are RESERVED.
// 
// Private Window Messages Start Here:
#define WM_USER                         0x0400
*/
#define UM_TEST	WM_USER + 1		// 自定义测试消息

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
					  // 窗口客户区创建消息，出来的是比较早的一个消息
					  // 此时窗口已经创建好了，只不过没有显示出来
					  // 只要使用 CreateWindow 或者 CreateWindowEx ，就发出这个信息
					  // 这是一个不进队列的消息，不需要GetMessage来进行获取
					  // wParam不使用
					  // lParam是一个结构体指针

					  // 创建一个指向名为cs的结构体的指针
					  //LPCREATESTRUCT cs;
					  // 第一个参数 创建窗口的时候传递的信息，
					  // 详见手册和视频
					  LPCREATESTRUCT lpcs = (LPCREATESTRUCT)lParam;

					  // MessageBox(NULL, L"Window Create", L"提示", MB_OK);
					  // 设置标题
					  SetWindowText(hWind, L"顿开教育");
					  break;
	}

	case UM_TEST:
	{
					MessageBox(hWind, L"用户自定义消息", L"提示", MB_OK);
					break;
	}

	case WM_LBUTTONDOWN:
	{
						   SendMessage(hWind, UM_TEST, 10, 10);
							// HWND hNodePad = FindWindow(L"NotePad", L"无标题 - 记事本");
							// if (hNodePad)
							// {
							//PostMessage(hNodePad, WM_CLOSE, 0, 0);
							// }
						   // 发送消息
						   // SendMessage
						   // PostMessage

						   // 发出WM_CLOSE消息
						   // SendMessage(hWind, WM_CLOSE, 0, 0);
						   // PostMessage(hWind, WM_CLOSE, 0, 0);

						   // 发出键盘按键消息
						   // SendMessage(hWind, WM_KEYDOWN, 0x41, 0);

		// 包含在<Windowsx>头文件中，可以用下面的函数代替
		// int x = GET_X_LPARAM(lParam);
		// int y = GET_Y_LPARAM(lParam);

		/*int x = LOWORD(lParam);
		int y = HIWORD(lParam);

		wchar_t szText[100] = { 0 };
		wsprintf(szText, L"当前鼠标坐标: (%d, %d)", x, y);
		if (wParam & MK_CONTROL)
		{
			wcscat(szText, L"ctrl按下");
		}
		if (wParam & MK_SHIFT)
		{
			wcscat(szText, L"shift按下");
		}
		if (wParam & MK_LBUTTON)
		{
			wcscat(szText, L"左键按下");
		}
		if (wParam & MK_MBUTTON)
		{
			wcscat(szText, L"中键按下");
		}
		if (wParam & MK_RBUTTON)
		{
			wcscat(szText, L"右键按下");
		}
		SetWindowText(hWind, szText);*/
		break;
	}
	case WM_MOUSEMOVE:
	{
						 int x = LOWORD(lParam);
						 int y = HIWORD(lParam);

						 wchar_t szText[100] = { 0 };
						 wsprintf(szText, L"当前鼠标坐标: (%d, %d)", x, y);
						 SetWindowText(hWind, szText);
						 break;
	}
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_RETURN:
			   MessageBox(hWind, L"按下了回车", L"提示", MB_OK);
			   break;
		case VK_SPACE:
			   MessageBox(hWind, L"按下了空格", L"提示", MB_OK);
			   break; 
		case VK_ESCAPE:
			   MessageBox(hWind, L"按下了Esc", L"提示", MB_OK);
			   break;
		case VK_F1:
			   MessageBox(hWind, L"按下了F1", L"提示", MB_OK);
			   break;
		case 0x41:
		{
					 wchar_t szText[] = L"按下A";
					 SetWindowText(hWind, szText);
					 // 如果高位是1，那么按下，否则抬起
					 // 如果低位是1，那么这个键已经被触发，例如大写键
					 short s = GetKeyState(VK_CONTROL);
					 if (s < 0)
					 {
						 MessageBox(hWind, L"Ctrl + A", L"提示", MB_OK);
					 }

					 break;
		}
		case VK_NUMPAD0:
			   MessageBox(hWind, L"按下了小键盘0", L"提示", MB_OK);
			   break;
		case 0x30:
			   MessageBox(hWind, L"按下了字母上方0", L"提示", MB_OK);
			   break;
		case VK_F3:
			   if (lParam >> 29 & 1)
			   {
				   MessageBox(hWind, L"按下了Alt + F3", L"提示", MB_OK);
			   }
			   break;
		}
		break;
	}
	case WM_CHAR:
	{
					wchar_t szText[100];
					wsprintf(szText, L"按下的键： %c", (char)wParam);
					SetWindowText(hWind, szText);
					break;
	}
	case WM_SIZE:
	{
					wchar_t szText[] = L"窗口大小改变";
					SetWindowText(hWind, szText);
					break;
	}
	case WM_PAINT:
	{
					 // 开始绘图
					 PAINTSTRUCT ps;
					 HDC dc = BeginPaint(hWind, &ps);

					 // 绘图过程
					 // 四边形
					 Rectangle(dc, 20, 20, 100, 100);
					 // 圆形和椭圆形
					 Ellipse(dc, 30, 30, 120, 150);
					 // 打印字
					 wchar_t szText[100] = L"嗷呜嗷呜";
					 TextOut(dc, 300, 300, szText, wcslen(szText));

					 // 结束绘图
					 EndPaint(hWind, &ps);

					 break;
	}
		// window message: close
	case WM_CLOSE:
		// wParam和lParam不使用
		/*DestroyWindow(hWind);*/
		if (IDYES == MessageBox(NULL, L"确定要关闭窗口吗？", L"提示", MB_YESNO))
		{
			DestroyWindow(hWind);
		}
		else
		{
			ShowWindow(hWind, SW_MINIMIZE);
			// 如果放break / 或是不放，那么就会到窗口的默认处理函数
			// 这样窗口也会关闭
			// 为了不调用窗口的默认函数，就需要自己解决
			// return 1;		// 不需要默认函数解决
			return 0;			// 如果我们没有解决，由默认函数解决
		}
		break;
		// window message: destroy
	case WM_DESTROY:
		// 清理工作
		// wParam和lParam不使用
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