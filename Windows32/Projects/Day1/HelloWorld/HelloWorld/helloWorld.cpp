// ʲô��API��Application Programming Interface��
	// Ӧ�ó����̽ӿ�
// Windows�ĺ����󲿷ֶ�����Windows.h��
#include <Windows.h>

// ʲô��SDK(Software Development Kit)
	// �����������������API�����⣬�����ֲỹ�и������ߣ�ʹ���ĵ�

// ʲô�Ǵ���
	// �������������˵�����ϵͳ�˵�����С������󻯿򣬹�����
	// ������Ҫ��Ϊ�ͻ����ͷǿͻ���

// ���
	// ������־�͹�����Դ
	// ���ھ����ͼ��������������˵���������̾��

// ���ڳ������ں�����WinMain
// ����̨����Ӧ�ó�����ں�����main

// ��������Լ��
// Լ���ˣ�
//		 1.	��������ջ��ʽ
//		 2.	��˭��ƽ���ջ
// WINAPI / CALLBACK / APIENTRYE����������������ջ�����õĺ��������ջ�����ʣ�__stdcall
// WINAPIV��__cdecl������������ջ

// ��һ������
// hInstance����ǰ�����ʵ�����
// HINSTANCE��
	// #define DECLARE_HANDLE(name) struct name##__{int unused;}; typedef struct name##__ *name
	// ������һ���ṹ��
	// ��name�滻�����name��##�����ӷ���ȥ������

// �ڶ�������
// hPreInstance����ǰ�����ǰһ��ʵ�����
	// ��16λ������ʹ��
	// ��32λ��64λ�������棬�Ѿ������������ڲ���ʹ�ã�ֵΪNULL

// ����������
// lpCmdLine�������в���
// LPSTR <==> char*
	// typedef char CHAR;
	// typedef CHAR *NPSTR, *LPSTR, *PSTR;	// CHAR* �ȼ��� NPSTR, LPSTR, PSTR

// ���ĸ�����
// nCmdShow�����ڵ���ʾ��ʽ��
		// ���
		// ��С��
		// ��ͨ
		// ������ʾ

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ����һ����Ϣ��ʾ��
	// L����˼�ǿ��ַ�
	MessageBox(NULL, L"Hello World!", L"��ܰ��ʾ", MB_OK);

	/*
	int WINAPI MessageBox(
	 _In_opt_  HWND hWnd,
	_In_opt_  LPCTSTR lpText,
	 _In_opt_  LPCTSTR lpCaption,
	 _In_      UINT uType
	);

	HWND: ���ھ�����ͣ����Ϊ���ڵ�ID

	LPCTSTR
		1.	LPCTSTR	Unicode����
			typedef LPCWSTR PCTSTR, LPCTSTR;				LPCWSTR <==> PCTSTR <==> LPCTSTR
			typedef CONST WCHAR *LPCWSTR, *PCWSTR			CONST WCHAR* <==> LPCWSTR <==> PCWSTR
			#define CONST const								CONST <==> const
			typedef wchar_t WCHAR							wchar_t <==> WCHAR
			const wchar_t* <==> LPCTSTR
		2.	LPCTSTR	���ֽ��ַ���
			typedef LPCTSTR PCTSTR, LPCTSTR;				LPCSTR <==> PCTSTR <==> LPCTSTR

	LPCTSTR <==> const wchar_t*
		typedef CONST WCHAR *LPCWSTR, *PCWSTR;
		LPCWSTR <==> PCTSTR <==> LPCTSTR
	
	��һ�������������ھ��
		���ڵ�ǰû�и����ڣ���˴�NULL
	�ڶ���������������Ϣ
	�������������������ͣ�����Ϊ�գ��յĺ���Ϊ������Ϣ  
	���ĸ���������ť��ͼ�����,�� | ���
		ֻ���԰�ť��ͼ����ϣ������Ĳ�������ϣ�������ʾ

	��������ֵ��������İ�ť
	*/

	

	return 0;
}