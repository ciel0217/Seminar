#include "CDxWindow.h"
#include "CDxApplication.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM IParam);

HRESULT CDxWindow::RegisterWindowClass(WNDCLASSEX* wnd)
{
	m_wndClass = {
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		m_hInstance,
		NULL,
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW+1),
		NULL,
		APP_NAME,
		NULL
	};

	HRESULT hr;
	hr = RegisterClassEx(&m_wndClass);



	*wnd = m_wndClass;

	return hr;
}

HRESULT CDxWindow::CreateMainWindow()
{
	m_hWnd = CreateWindow(APP_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2,
		SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),
		NULL,
		NULL,
		m_hInstance,
		NULL
	);

	if (!m_hWnd) {
		return S_FALSE;
	}

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return S_OK;
}

LRESULT CDxWindow::LocalWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM IParam)
{
	switch(msg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_KEYDOWN:
			switch (wParam)
			{
				case VK_ESCAPE:
				DestroyWindow(hWnd);
				break;
			default:
				break;
			}
		default:
			return DefWindowProc(hWnd, msg, wParam, IParam);
	}
	return 1;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM IParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		default:
			break;
		}
	default:
		return DefWindowProc(hWnd, msg, wParam, IParam);
	}
	return 0;
}