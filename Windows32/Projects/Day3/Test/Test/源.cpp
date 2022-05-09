#include <Windows.h>
#include "resource.h"

HINSTANCE g_hInstance;	// 应用程序实例句柄

BOOL CALLBACK ChatDialogProc(HWND hWind, UINT uMSG, WPARAM wParam, LPARAM lParam)
{
	switch (uMSG)
	{
	case WM_CLOSE:
		// EndDialog并不是真正的关闭非模态对话框，而是隐藏
		EndDialog(hWind, IDCLOSE);
		// 只有DestroyWindow才能真正的关闭非模态对话框
		DestroyWindow(hWind);
		break;
	case WM_COMMAND:
		switch (wParam)
		{
		case IDOK:
		{
			
		}
			// 取消，关闭对话框
		case IDCANCEL:
			EndDialog(hWind, IDCANCEL);
			break;
		}
		break;
	default:
		break;
	}

	return FALSE;
}

BOOL CALLBACK LoginDialogProc(HWND hWind, UINT uMSG, WPARAM wParam, LPARAM lParam)
{
	

	switch (uMSG)
	{
	case WM_CLOSE:
		EndDialog(hWind, IDCLOSE);
		break;
	case WM_COMMAND:
		switch (wParam)
		{
		case IDOK:
		{
					 wchar_t szUsername[100];
					 wchar_t szUserpass[100];

					 GetDlgItemText(hWind, IDC_USERNAME, szUsername, 100);
					 GetDlgItemText(hWind, IDC_USERPASS, szUserpass, 100);

					 MessageBox(hWind, szUsername, L"用户名", MB_OK);

					 // 用户名和密码正确
					 if (wcscmp(szUsername, L"admin") == 0 && wcscmp(szUserpass, L"123") == 0)
					 {
						 // 成功，关闭当前窗口
						 EndDialog(hWind, IDOK);
					 }
					 else
					 {
						 MessageBox(hWind, L"密码错误", L"提示", MB_OK);
					 }

					 break;
		}
		// 取消，关闭对话框
		case IDCANCEL:
			EndDialog(hWind, IDCANCEL);
			break;
		}
		break;
	default:
		break;
	}
	return FALSE;
}

BOOL CALLBACK InfoDialogProc(HWND hWind, UINT uMSG, WPARAM wParam, LPARAM lParam)
{
	switch (uMSG)
	{
	case WM_COMMAND:
		switch (wParam)
		{
		default:
			EndDialog(hWind, MB_OK);
			break;
		}
		break;

	default:
		break;
	}

	return FALSE;
}

BOOL CALLBACK MainDialogProc(HWND hWind, UINT uMSG, WPARAM wParam, LPARAM lParam)
{
	static HWND hChatDlg = NULL;

	switch (uMSG)
	{
	// 在对话框中，对话框不响应WM_CREATE
	// 已经被WM_INITDIALOG接管
	// 但是在MFC中被实现
	/*case WM_CREATE:
		MessageBox(hWind, L"WM_CREATE", L"提示", MB_OK);
		break;*/

	// 初始化对话框，此时对话框还没有显示，但是对话框已经被创建好了
	case WM_INITDIALOG:
	{

						  // SetWindowText(hWind, L"这是一个对话框程序");

							// 设置图标
							// 加载图标
							HICON hIcon = LoadIcon(g_hInstance, MAKEINTRESOURCE(ICON_MAIN));

							// 发送消息
							SendMessage(hWind, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
							SendMessage(hWind, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);

							break;
	}
		

	// 命令消息
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDCANCEL:
			EndDialog(hWind, IDCANCEL);
			break;
		case IDOK:
			// MessageBox(hWind, L"点击了确定按钮", L"提示", MB_OK);
			break;
		case IDC_INFO:
			DialogBox(g_hInstance, (LPCWSTR)IDD_INFO, hWind, InfoDialogProc);
			break; 
		case IDC_BTM_CHAT:
			// 创建非模态窗口，并返回其窗口句柄
			// 非阻塞
			hChatDlg = CreateDialog(g_hInstance, (LPCWSTR)IDD_DLG_CHAT, hWind, ChatDialogProc);
			// 显示窗口
			ShowWindow(hChatDlg, SW_SHOW);
			// 更新窗口
			UpdateWindow(hChatDlg);

			break;
			// 显示已经关闭的窗口
		case IDC_BTM_SHOW:
			// 显示窗口
			ShowWindow(hChatDlg, SW_SHOW);
			// 只要调用ShowWindow 、 UpdateWindow，都会发出WM_paint消息
			break;
		}
		break;

	// 关闭消息
	case WM_CLOSE:
		// 第二个参数会作为窗口结束的返回值，作为DialogBox的返回值
		EndDialog(hWind, 3);
		break;
	}

	// 一定要写return FALSE
	// 这和消息处理一样，return 0就是交给操作系统处理函数去处理
	return FALSE;
}




int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	g_hInstance = hInstance;

	// 1.	模态对话框
	// 创建: DialogBox
	// 结束: EndDialog

	// 创建登录窗口
	int nResult = DialogBox(hInstance, (LPCTSTR)IDD_LOGIN_DLG, NULL, LoginDialogProc);
	if (nResult == IDOK)
	{
		// 创建主窗口
		DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN_DLG), NULL, MainDialogProc);
	}	

	// 2.	非模态对话框
	// 创建：CreateDialog函数
	// 关闭：DestroyWindow函数



}