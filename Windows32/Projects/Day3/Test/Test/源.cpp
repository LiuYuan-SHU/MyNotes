#include <Windows.h>
#include "resource.h"

HINSTANCE g_hInstance;	// Ӧ�ó���ʵ�����

BOOL CALLBACK ChatDialogProc(HWND hWind, UINT uMSG, WPARAM wParam, LPARAM lParam)
{
	switch (uMSG)
	{
	case WM_CLOSE:
		// EndDialog�����������Ĺرշ�ģ̬�Ի��򣬶�������
		EndDialog(hWind, IDCLOSE);
		// ֻ��DestroyWindow���������Ĺرշ�ģ̬�Ի���
		DestroyWindow(hWind);
		break;
	case WM_COMMAND:
		switch (wParam)
		{
		case IDOK:
		{
			
		}
			// ȡ�����رնԻ���
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

					 MessageBox(hWind, szUsername, L"�û���", MB_OK);

					 // �û�����������ȷ
					 if (wcscmp(szUsername, L"admin") == 0 && wcscmp(szUserpass, L"123") == 0)
					 {
						 // �ɹ����رյ�ǰ����
						 EndDialog(hWind, IDOK);
					 }
					 else
					 {
						 MessageBox(hWind, L"�������", L"��ʾ", MB_OK);
					 }

					 break;
		}
		// ȡ�����رնԻ���
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
	// �ڶԻ����У��Ի�����ӦWM_CREATE
	// �Ѿ���WM_INITDIALOG�ӹ�
	// ������MFC�б�ʵ��
	/*case WM_CREATE:
		MessageBox(hWind, L"WM_CREATE", L"��ʾ", MB_OK);
		break;*/

	// ��ʼ���Ի��򣬴�ʱ�Ի���û����ʾ�����ǶԻ����Ѿ�����������
	case WM_INITDIALOG:
	{

						  // SetWindowText(hWind, L"����һ���Ի������");

							// ����ͼ��
							// ����ͼ��
							HICON hIcon = LoadIcon(g_hInstance, MAKEINTRESOURCE(ICON_MAIN));

							// ������Ϣ
							SendMessage(hWind, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
							SendMessage(hWind, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);

							break;
	}
		

	// ������Ϣ
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDCANCEL:
			EndDialog(hWind, IDCANCEL);
			break;
		case IDOK:
			// MessageBox(hWind, L"�����ȷ����ť", L"��ʾ", MB_OK);
			break;
		case IDC_INFO:
			DialogBox(g_hInstance, (LPCWSTR)IDD_INFO, hWind, InfoDialogProc);
			break; 
		case IDC_BTM_CHAT:
			// ������ģ̬���ڣ��������䴰�ھ��
			// ������
			hChatDlg = CreateDialog(g_hInstance, (LPCWSTR)IDD_DLG_CHAT, hWind, ChatDialogProc);
			// ��ʾ����
			ShowWindow(hChatDlg, SW_SHOW);
			// ���´���
			UpdateWindow(hChatDlg);

			break;
			// ��ʾ�Ѿ��رյĴ���
		case IDC_BTM_SHOW:
			// ��ʾ����
			ShowWindow(hChatDlg, SW_SHOW);
			// ֻҪ����ShowWindow �� UpdateWindow�����ᷢ��WM_paint��Ϣ
			break;
		}
		break;

	// �ر���Ϣ
	case WM_CLOSE:
		// �ڶ�����������Ϊ���ڽ����ķ���ֵ����ΪDialogBox�ķ���ֵ
		EndDialog(hWind, 3);
		break;
	}

	// һ��Ҫдreturn FALSE
	// �����Ϣ����һ����return 0���ǽ�������ϵͳ������ȥ����
	return FALSE;
}




int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	g_hInstance = hInstance;

	// 1.	ģ̬�Ի���
	// ����: DialogBox
	// ����: EndDialog

	// ������¼����
	int nResult = DialogBox(hInstance, (LPCTSTR)IDD_LOGIN_DLG, NULL, LoginDialogProc);
	if (nResult == IDOK)
	{
		// ����������
		DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN_DLG), NULL, MainDialogProc);
	}	

	// 2.	��ģ̬�Ի���
	// ������CreateDialog����
	// �رգ�DestroyWindow����



}