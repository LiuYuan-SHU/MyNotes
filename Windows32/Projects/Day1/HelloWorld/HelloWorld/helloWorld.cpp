// 什么是API（Application Programming Interface）
	// 应用程序编程接口
// Windows的函数大部分都放在Windows.h里
#include <Windows.h>

// 什么是SDK(Software Development Kit)
	// 软件开发包，包含了API函数库，帮助手册还有辅助工具，使用文档

// 什么是窗口
	// 包含标题栏、菜单栏、系统菜单、最小化框，最大化框，滚动条
	// 窗口主要分为客户区和非客户区

// 句柄
	// 用来标志和管理资源
	// 窗口句柄、图标句柄、光标句柄、菜单句柄、进程句柄

// 窗口程序的入口函数：WinMain
// 控制台窗口应用程序入口函数：main

// 函数调用约定
// 约定了：
//		 1.	函数的入栈方式
//		 2.	由谁来平衡堆栈
// WINAPI / CALLBACK / APIENTRYE：参数从右往左入栈，调用的函数清理堆栈，本质：__stdcall
// WINAPIV：__cdecl：从右往左入栈

// 第一个参数
// hInstance：当前程序的实例句柄
// HINSTANCE：
	// #define DECLARE_HANDLE(name) struct name##__{int unused;}; typedef struct name##__ *name
	// 定义了一个结构体
	// 用name替换后面的name，##是连接符，去掉即可

// 第二个参数
// hPreInstance：当前程序的前一个实例句柄
	// 在16位机器上使用
	// 在32位和64位机器上面，已经被废弃，现在不再使用，值为NULL

// 第三个参数
// lpCmdLine：命令行参数
// LPSTR <==> char*
	// typedef char CHAR;
	// typedef CHAR *NPSTR, *LPSTR, *PSTR;	// CHAR* 等价于 NPSTR, LPSTR, PSTR

// 第四个参数
// nCmdShow：窗口的显示方式：
		// 最大化
		// 最小化
		// 普通
		// 正常显示

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 弹出一个消息提示框
	// L的意思是宽字符
	MessageBox(NULL, L"Hello World!", L"温馨提示", MB_OK);

	/*
	int WINAPI MessageBox(
	 _In_opt_  HWND hWnd,
	_In_opt_  LPCTSTR lpText,
	 _In_opt_  LPCTSTR lpCaption,
	 _In_      UINT uType
	);

	HWND: 窗口句柄类型，理解为窗口的ID

	LPCTSTR
		1.	LPCTSTR	Unicode编码
			typedef LPCWSTR PCTSTR, LPCTSTR;				LPCWSTR <==> PCTSTR <==> LPCTSTR
			typedef CONST WCHAR *LPCWSTR, *PCWSTR			CONST WCHAR* <==> LPCWSTR <==> PCWSTR
			#define CONST const								CONST <==> const
			typedef wchar_t WCHAR							wchar_t <==> WCHAR
			const wchar_t* <==> LPCTSTR
		2.	LPCTSTR	多字节字符集
			typedef LPCTSTR PCTSTR, LPCTSTR;				LPCSTR <==> PCTSTR <==> LPCTSTR

	LPCTSTR <==> const wchar_t*
		typedef CONST WCHAR *LPCWSTR, *PCWSTR;
		LPCWSTR <==> PCTSTR <==> LPCTSTR
	
	第一个参数：父窗口句柄
		由于当前没有父窗口，因此传NULL
	第二个参数：窗口信息
	第三个参数：窗口类型，可以为空，空的含义为错误信息  
	第四个参数：按钮和图标组合,用 | 组合
		只可以按钮和图标组合，其他的不可以组合，否则不显示

	函数返回值：被点击的按钮
	*/

	

	return 0;
}