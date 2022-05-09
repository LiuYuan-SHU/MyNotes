#include <Windows.h>
#include "resource.h"

// �߼�����������ȫ�ֱ��������浱ǰ����ʵ��
HINSTANCE g_hInstance = NULL;

BOOL CALLBACK InfoDlgProc(HWND hWind, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		// �رմ���
	case WM_CLOSE:
		EndDialog(hWind, IDCLOSE);
		break;
	case WM_COMMAND:
		EndDialog(hWind, IDCLOSE);
		break;
	}

	return FALSE;
}

BOOL CALLBACK ChatDlgProc(HWND hWind, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		// �رմ���
	case WM_CLOSE:
		DestroyWindow(hWind);
		break;
	case WM_COMMAND:
		DestroyWindow(hWind);
		break;
	}

	return FALSE;
}

BOOL CALLBACK LoginDlgProc(HWND hWind, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	// �رմ���
	case WM_CLOSE:
		EndDialog(hWind, IDCLOSE);
		break;
	// ���ڰ�ť��Ϣ
	case WM_COMMAND:
	{
					   switch (wParam)
					   {
					   case IDCANCEL:
						   EndDialog(hWind, IDCANCEL);
						   break;
					   case IDOK:
					   {
									wchar_t szTextUsername[100];
									wchar_t szTextUserPass[100];

									GetDlgItemText(hWind, IDC_USER_NAME, szTextUsername, 100);
									GetDlgItemText(hWind, IDC_USER_PASS, szTextUserPass, 100);

									if (wcscmp(szTextUsername, L"admin") == 0 && wcscmp(szTextUserPass, L"123") == 0)
									{
										EndDialog(hWind, IDOK); 
									}
									else
									{
										MessageBox(hWind, L"�������", L"��ʾ", MB_OK);
									}

									break;
					   }
					   default:
						   break;
					   }
					   break;
	}

	default:
		break;
	}

	return FALSE;
}

BOOL CALLBACK MainDlgProc(HWND hWind, UINT uMsg, WPARAM wParam, LPARAM lParam)
{ 
	switch (uMsg)
	{
	// ��ʼ�����ڵ�ͬʱ����ͼ��
	case WM_INITDIALOG:
	{
		HICON hIcon = LoadIcon(g_hInstance, MAKEINTRESOURCE(IDI_ICON));
		SendMessage(hWind, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
		SendMessage(hWind, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);

		break;
	}
	// ���ڰ�ť��Ϣ
	case WM_COMMAND:
	{
		switch (wParam)
		{
		// ���촰��
		case IDC_BTN_CHAT:
		{
			HWND hDialogChat = CreateDialog(g_hInstance, MAKEINTRESOURCE(ID_DLG_CHAT), hWind, ChatDlgProc);
			ShowWindow(hDialogChat, SW_SHOW);
			UpdateWindow(hDialogChat);
			break;
		}
		// ��������
		case IDC_BTN_INFO:
		{
			DialogBox(g_hInstance, MAKEINTRESOURCE(ID_DLG_INFO), hWind, InfoDlgProc);
			break;
		}
		default:
			break;
		}
		break;
	}
	// �رմ���
	case WM_CLOSE:
	{
		EndDialog(hWind, IDCLOSE);
		break;
	}
	}

	return FALSE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ��¼��ǰ����ʵ������
	g_hInstance = hInstance;

	int nLoginResult = DialogBox(g_hInstance, MAKEINTRESOURCE(ID_DLG_LOGIN), NULL, LoginDlgProc);
	if (nLoginResult == IDOK)
	{
		// ������¼�Ի���
		DialogBox(g_hInstance, MAKEINTRESOURCE(ID_DLG_MAIN), NULL, MainDlgProc);
	}
	
	return 0;
}