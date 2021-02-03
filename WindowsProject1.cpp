#ifndef UNICODE
#define UNICODE
#endif // UNICODE
#pragma warning(disable:4996);
#include "framework.h"
#include "WindowsProject1.h"
#include <windowsx.h>
#include <Windows.h>
#include <d2d1.h>
#include "basewin.h"
#include <stdio.h>
#include "resource1.h"
#define WM_AAA WM_USER+1



class MainWindow :public BaseWindow<MainWindow>
{
public:
	PCWSTR ClassName() const { return L"Sample Window Class"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
		switch (uMsg)
		{

		case WM_CREATE: {

			//创建位图图标
			HWND hBtn = CreateWindow(L"button",
				L"普通按钮",
				WS_CHILD | WS_VISIBLE | BS_BITMAP,
				15, 10,
				100, 40,
				m_hwnd,
				(HMENU)1000,
				pcs->hInstance,
				NULL
			);
			// LoadImage创建位图
			//HBITMAP hBmp = (HBITMAP)LoadImage(NULL, L"E:\\Cplus\\WindowsProject\\WindowsProject1\\Debug\\bitmap1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			HBITMAP hBmp = (HBITMAP)LoadBitmap(pcs->hInstance, MAKEINTRESOURCE(IDB_BITMAP1));
			SendMessage(hBtn, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hBmp);



			HWND hBtn1 = CreateWindow(L"button",
				L"单选按钮",
				WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
				15, 50,
				100, 30,
				m_hwnd,
				(HMENU)1001,
				pcs->hInstance,
				NULL
			);

			HWND hBtn2 = CreateWindow(L"button",
				L"复选按钮",
				WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
				15, 100,
				100, 30,
				m_hwnd,
				(HMENU)1002,
				pcs->hInstance,
				NULL
			);

			HWND hText = CreateWindow(L"static",
				L"测试文字啊实打实的",
				WS_VISIBLE | WS_CHILD | SS_BITMAP |SS_NOTIFY,
				15, 140,
				100, 100,
				m_hwnd,
				(HMENU)1003,
				pcs->hInstance,
				NULL
			);

			HBITMAP hb = (HBITMAP)LoadImage(pcs->hInstance, MAKEINTRESOURCE(IDB_BITMAP2), IMAGE_BITMAP, 0, 0, LR_SHARED);//加载项目里面资源的时候，hInstance加上
			LRESULT ret = SendMessage(hText, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hb);

			return 0;
		}
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_COMMAND:
		{
			WORD id = LOWORD(wParam);
			WORD code = HIWORD(wParam);
			HWND hCtrl = (HWND)lParam;
			if (id == 1000)
			{

				MessageBox(NULL, L"普通按钮被点击", L"提示", MB_OK);


			}
			else if (id == 1001)
			{
				MessageBox(NULL, L"单选按钮被点击", L"提示", MB_OK);
				if (SendMessage(hCtrl, BM_GETCHECK, 0, 0) == BST_CHECKED)
				{
					MessageBox(NULL, L"单选按钮被勾选", L"提示", MB_OK);
				}
			}
			else if (id == 1002)
			{
				MessageBox(NULL, L"复选框按钮被点击", L"提示", MB_OK);
				if (Button_GetCheck(hCtrl) == BST_CHECKED)
				{
					MessageBox(NULL, L"复选框被勾选", L"提示", MB_OK);
				}
			}
			else if (id == 1003) {
				//静态文本
				if (code == STN_CLICKED) {
					MessageBox(NULL, L"静态文本被点击", L"提示", MB_OK);
				}
			}

		}
		default:
			return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
		}
		return TRUE;
	};
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, INT nCmdShow) {
	MainWindow win1;

	TCHAR str[64] = { 0 };
	LoadString(hInstance, IDS_STRING1, str, sizeof(str));

	if (!win1.Create(str, WS_OVERLAPPEDWINDOW)) {
		return 0;
	}

	ShowWindow(win1.Window(), nCmdShow);
	UpdateWindow(win1.Window());

	MSG msg = {};
	while (GetMessageW(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}
