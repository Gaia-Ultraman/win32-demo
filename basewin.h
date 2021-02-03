#pragma once
template <class DERIVED_TYPE>
class BaseWindow
{
public:
	static LRESULT CALLBACK MyWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		DERIVED_TYPE* pThis = NULL;
		if (uMsg == WM_NCCREATE)
		{
			CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
			pThis = (DERIVED_TYPE*)pCreate->lpCreateParams;
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);
			pThis->m_hwnd = hwnd;
		}
		else
		{
			pThis = (DERIVED_TYPE*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		}

		if (pThis)
		{
			return pThis->HandleMessage(uMsg, wParam, lParam);
		}
		else
		{
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}

	BaseWindow() :m_hwnd(NULL) {}

	BOOL Create(
		PCWSTR lpWindowName,
		DWORD dwStyle,
		int x = 100,
		int y = 100,
		int nHeight = 300,
		int nWidth = 300,
		HWND hWndParent = 0,
		HMENU hMenu = 0
	)
	{
		HINSTANCE hInstance = GetModuleHandle(NULL);
		WNDCLASS wc = { 0 };
		wc.lpfnWndProc = DERIVED_TYPE::MyWindowProc;
		wc.hInstance = hInstance;
		wc.lpszClassName = ClassName();
		wc.hbrBackground = CreateSolidBrush(RGB(255, 0, 0));
		wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));//加载本项目里面自定义的图标第一个参数不能为NULL
		wc.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
		wc.style = CS_HREDRAW | CS_DBLCLKS;
		RegisterClass(&wc);

		m_hwnd = CreateWindow(
			ClassName(), lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, GetModuleHandle(NULL), this
		);

		return (m_hwnd ? TRUE : FALSE);
	}

	HWND Window() const { return m_hwnd; }

protected:
	virtual PCWSTR ClassName() const = 0;
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
	HWND m_hwnd;
};
