#pragma once
#include "DirectX.h"
#include <memory>

class CDxWindow;

class CDxApplication {
private:
	HINSTANCE m_hInstance;
	WNDCLASSEX m_WndClassWx;
	std::unique_ptr<CDxWindow> m_DxWindow;

	bool RegiterWndClass();
	bool CreateMainWnd();
	bool Initialize();
	void Loop();
	void ReleaseApp();
	void Update();
	void Draw();

	int m_CountFPS;
	char m_DebugStr[2048] = "aaaa";

public:
	CDxApplication();
	~CDxApplication() {};
	static LRESULT CALLBACK GrobalWndProc(HWND, UINT, WPARAM, LPARAM);

	int Run(HINSTANCE hInstance);

	HINSTANCE GetHInstance() { return m_hInstance; }

	void GetWndClass(WNDCLASSEX * wc) {
		*wc = m_WndClassWx;
	}

	CDxWindow* GetDxWindow() { return m_DxWindow.get(); }
};