#include <Windows.h>
#include "resource1.h"

// 窗口处理函数
LRESULT CALLBACK WindowProc(HWND hWind, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// LRESULT	表示处理结果
	// typedef UINT_PTR            WPARAM;
	// typedef LONG_PTR            LPARAM;
	// typedef LONG_PTR            LRESULT;

	/*
	第一个参数：窗口句柄
		表示当前窗口的窗口句柄
	第二个参数：消息编号
	第三个参数：窗口附加信息
		WPARAM：假如鼠标点击，点击的坐标就是附加信息
	第四个参数：窗口附加信息
		LPARAM：
	*/
	switch (uMsg)
	{
	case WM_CLOSE:	// 窗口关闭消息
		// MessageBox(NULL, L"点了关闭", L"提示", MB_OK);
		DestroyWindow(hWind);	// 销毁窗口，发出WM_DESTROY消息
		break;
	case WM_DESTROY:// 窗口销毁消息
		PostQuitMessage(0);		// 发出一个退出消息 WM_QUIT,正常退出代码 0
		break;
	}

	// 操作系统默认处理的函数
	return DefWindowProc(hWind, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 一、设计窗口类
	WNDCLASS wc;
	wchar_t szAppClassName[] = L"Dunkai Education GUI";
	wchar_t szWindowName[] = L"这是我的第一个Windows程序";

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

	wc.style = CS_HREDRAW | CS_VREDRAW;						// 窗口类的风格，当宽高方向进行拉伸，重绘窗口
	wc.lpfnWndProc = WindowProc;							// 窗口处理函数
	wc.cbClsExtra = 0;										// 窗口类的额外拓展大小（字节）
	wc.cbWndExtra = 0;										// 窗口的额外扩展空间大小（字节）
	wc.hInstance = hInstance;								// 当前应用程序实例句柄
	// DECLARE_HANDLE(HICON);
		// h 开头的一般都是句柄
	// LoadIcon
		// 参数
			// 第一个参数：应用程序实例句柄
				// 如果是系统资源，传递NULL
				// 如果是自定义资源，传递hInstance
			// 第二个参数：资源ID
	// 窗口左上角的图标，NULL代表没有图标
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAIN));		
	// 鼠标图标句柄，NULL代表没有设置
	// 渲染箭头
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);										

	// #define RGB(r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
	wc.hbrBackground = CreateSolidBrush(RGB(255,255,255));	// 背景画刷句柄，取值范围为(0 ~ 255)

	wc.lpszMenuName = NULL;									// 菜单名称
	wc.lpszClassName = szAppClassName;						// 类名称

	// 二、注册窗口类
	/*
	typedef unsigned short      WORD;
	typedef WORD                ATOM;
	
	ATOM WINAPI RegisterClass(
	_In_  const WNDCLASS *lpWndClass
	);

	返回值：
		If the function succeeds, the return value is a class atom that uniquely identifies the class being registered.
		If the function fails, the return value is zero.
	*/

	if (RegisterClass(&wc) == 0)
	{
		MessageBox(NULL, L"此程序不能在Windows NT上运行", L"温馨提示", MB_OK);
		return -1;
	}

	// 三、创建窗口
	// 如果成功，返回一个新的窗口句柄
	HWND hWind = CreateWindow(
		szAppClassName,		// 窗口类型名
		szWindowName,		// 窗口名称
		WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX,	// 窗口的风格
		200,				// 窗口左上角横坐标
		200,				// 窗口左上角纵坐标
		800,				// 窗口的宽度
		600,				// 窗口的高度
		NULL,				// 父窗口句柄
		NULL,				// 菜单句柄
		hInstance,			// 应用程序实例句柄
		NULL				// 创建窗口的时候传递的信息
		);

	if (hWind == NULL)
	{
		MessageBox(NULL, L"创建窗口失败", L"温馨提示", NULL);
	}

	// 四、显示窗口
	ShowWindow(hWind, SW_SHOW);

	// 五、更新窗口
	UpdateWindow(hWind);

	// 六、消息循环
	// Message structure
	/*
	typedef struct tagMSG {
	HWND        hwnd;			// 消息发给哪一个窗口的窗口句柄
	UINT        message;		// 消息编号
	WPARAM      wParam;			// 附加信息
	LPARAM      lParam;			// 附加信息
	DWORD       time;			// 消息投放到消息队列里面的时间
	POINT       pt;				// 消息放入消息队列的时候鼠标的坐标
#ifdef _MAC
	DWORD       lPrivate;
#endif
	} MSG, *PMSG, NEAR *NPMSG, FAR *LPMSG;
	*/
	MSG msg;
	/*
	BOOL WINAPI GetMessage(
	  _Out_     LPMSG lpMsg,			// 消息指针
	  _In_opt_  HWND hWnd,				// 句柄
	  _In_      UINT wMsgFilterMin,		// 编号的最小值
	  _In_      UINT wMsgFilterMax		// 编号的最大值
	);

	返回值：只要收到了 WM_QUIT 消息，就返回0
	*/
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		// 将虚拟键消息转为字符消息
		TranslateMessage(&msg);
		// 将虚拟键分发给窗口处理函数
		DispatchMessage(&msg);
	}

	return 0;
}