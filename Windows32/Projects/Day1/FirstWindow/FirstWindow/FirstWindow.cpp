#include <Windows.h>
#include "resource1.h"

// ���ڴ�����
LRESULT CALLBACK WindowProc(HWND hWind, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// LRESULT	��ʾ������
	// typedef UINT_PTR            WPARAM;
	// typedef LONG_PTR            LPARAM;
	// typedef LONG_PTR            LRESULT;

	/*
	��һ�����������ھ��
		��ʾ��ǰ���ڵĴ��ھ��
	�ڶ�����������Ϣ���
	���������������ڸ�����Ϣ
		WPARAM������������������������Ǹ�����Ϣ
	���ĸ����������ڸ�����Ϣ
		LPARAM��
	*/
	switch (uMsg)
	{
	case WM_CLOSE:	// ���ڹر���Ϣ
		// MessageBox(NULL, L"���˹ر�", L"��ʾ", MB_OK);
		DestroyWindow(hWind);	// ���ٴ��ڣ�����WM_DESTROY��Ϣ
		break;
	case WM_DESTROY:// ����������Ϣ
		PostQuitMessage(0);		// ����һ���˳���Ϣ WM_QUIT,�����˳����� 0
		break;
	}

	// ����ϵͳĬ�ϴ���ĺ���
	return DefWindowProc(hWind, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// һ����ƴ�����
	WNDCLASS wc;
	wchar_t szAppClassName[] = L"Dunkai Education GUI";
	wchar_t szWindowName[] = L"�����ҵĵ�һ��Windows����";

	/*
	typedef struct tagWNDCLASSW {
	UINT        style;
	WNDPROC     lpfnWndProc;
	int         cbClsExtra;
	int         cbWndExtra;
	HINSTANCE   hInstance;
	HICON       hIcon;
	HCURSOR     hCursor;
	HBRUSH      hbrBackground;
	LPCWSTR     lpszMenuName;
	LPCWSTR     lpszClassName;
	} WNDCLASSW;

	#ifdef UNICODE
	typedef WNDCLASSW WNDCLASS;
	*/

	wc.style = CS_HREDRAW | CS_VREDRAW;						// ������ķ�񣬵���߷���������죬�ػ洰��
	wc.lpfnWndProc = WindowProc;							// ���ڴ�����
	wc.cbClsExtra = 0;										// ������Ķ�����չ��С���ֽڣ�
	wc.cbWndExtra = 0;										// ���ڵĶ�����չ�ռ��С���ֽڣ�
	wc.hInstance = hInstance;								// ��ǰӦ�ó���ʵ�����
	// DECLARE_HANDLE(HICON);
		// h ��ͷ��һ�㶼�Ǿ��
	// LoadIcon
		// ����
			// ��һ��������Ӧ�ó���ʵ�����
				// �����ϵͳ��Դ������NULL
				// ������Զ�����Դ������hInstance
			// �ڶ�����������ԴID
	// �������Ͻǵ�ͼ�꣬NULL����û��ͼ��
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAIN));		
	// ���ͼ������NULL����û������
	// ��Ⱦ��ͷ
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);										

	// #define RGB(r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
	wc.hbrBackground = CreateSolidBrush(RGB(255,255,255));	// ������ˢ�����ȡֵ��ΧΪ(0 ~ 255)

	wc.lpszMenuName = NULL;									// �˵�����
	wc.lpszClassName = szAppClassName;						// ������

	// ����ע�ᴰ����
	/*
	typedef unsigned short      WORD;
	typedef WORD                ATOM;
	
	ATOM WINAPI RegisterClass(
	_In_  const WNDCLASS *lpWndClass
	);

	����ֵ��
		If the function succeeds, the return value is a class atom that uniquely identifies the class being registered.
		If the function fails, the return value is zero.
	*/

	if (RegisterClass(&wc) == 0)
	{
		MessageBox(NULL, L"�˳�������Windows NT������", L"��ܰ��ʾ", MB_OK);
		return -1;
	}

	// ������������
	// ����ɹ�������һ���µĴ��ھ��
	HWND hWind = CreateWindow(
		szAppClassName,		// ����������
		szWindowName,		// ��������
		WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX,	// ���ڵķ��
		200,				// �������ϽǺ�����
		200,				// �������Ͻ�������
		800,				// ���ڵĿ��
		600,				// ���ڵĸ߶�
		NULL,				// �����ھ��
		NULL,				// �˵����
		hInstance,			// Ӧ�ó���ʵ�����
		NULL				// �������ڵ�ʱ�򴫵ݵ���Ϣ
		);

	if (hWind == NULL)
	{
		MessageBox(NULL, L"��������ʧ��", L"��ܰ��ʾ", NULL);
	}

	// �ġ���ʾ����
	ShowWindow(hWind, SW_SHOW);

	// �塢���´���
	UpdateWindow(hWind);

	// ������Ϣѭ��
	// Message structure
	/*
	typedef struct tagMSG {
	HWND        hwnd;			// ��Ϣ������һ�����ڵĴ��ھ��
	UINT        message;		// ��Ϣ���
	WPARAM      wParam;			// ������Ϣ
	LPARAM      lParam;			// ������Ϣ
	DWORD       time;			// ��ϢͶ�ŵ���Ϣ���������ʱ��
	POINT       pt;				// ��Ϣ������Ϣ���е�ʱ����������
#ifdef _MAC
	DWORD       lPrivate;
#endif
	} MSG, *PMSG, NEAR *NPMSG, FAR *LPMSG;
	*/
	MSG msg;
	/*
	BOOL WINAPI GetMessage(
	  _Out_     LPMSG lpMsg,			// ��Ϣָ��
	  _In_opt_  HWND hWnd,				// ���
	  _In_      UINT wMsgFilterMin,		// ��ŵ���Сֵ
	  _In_      UINT wMsgFilterMax		// ��ŵ����ֵ
	);

	����ֵ��ֻҪ�յ��� WM_QUIT ��Ϣ���ͷ���0
	*/
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		// ���������ϢתΪ�ַ���Ϣ
		TranslateMessage(&msg);
		// ��������ַ������ڴ�����
		DispatchMessage(&msg);
	}

	return 0;
}