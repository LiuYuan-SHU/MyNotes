#define _AFXDLL

// application framework X Windows
#include <afxwin.h>
#include <CString.h>
// MFC����������
// ��һ��������CWinApp������
// �ڶ�������дCWinApp�����InitInstance�麯��
// ������������CWinApp�������ȫ�ֶ���
class CMyApp : public CWinApp
{
public:
	BOOL InitInstance()
	{
		MessageBox(NULL, L"InitInstance", L"��ʾ", MB_OK);
		return TRUE;
	}
};

CMyApp theApp;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CString cs;

	return 0;
}