#pragma once
#include"main.h"
#define WINDOW_NAME "test"
#define APP_NAME "app"
class Window{
private:
	HWND m_hWnd;
	HINSTANCE m_hInstance;
	WNDCLASSEX m_wndClass;

public:
	Window() = delete;
	Window(HINSTANCE hInstance) :m_hInstance(hInstance) {};
	~Window() {};

	HRESULT RegisterWindowClass(WNDCLASSEX* wnd);
	HRESULT CreateMainWindow();
	LRESULT LocalWndProc(HWND, UINT, WPARAM, LPARAM);

	HWND GetHWND() { return m_hWnd; }
};
