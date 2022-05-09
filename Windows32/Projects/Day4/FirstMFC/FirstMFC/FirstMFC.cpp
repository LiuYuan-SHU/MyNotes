#define _AFXDLL

// application framework X Windows
#include <afxwin.h>
#include <CString.h>
// MFC程序三部曲
// 第一步：建立CWinApp派生类
// 第二步：重写CWinApp里面的InitInstance虚函数
// 第三步：定义CWinApp派生类的全局对象
class CMyApp : public CWinApp
{
public:
	BOOL InitInstance()
	{
		MessageBox(NULL, L"InitInstance", L"提示", MB_OK);
		return TRUE;
	}
};

CMyApp theApp;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CString cs;

	return 0;
}