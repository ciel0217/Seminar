#pragma once
#include "DirectX.h"
#include <memory>

class CDxWindow;

class CDxApplication
{
private:
	HINSTANCE m_hinstance;
	WNDCLASSEX m_WndclassWx;
	std::unique_ptr<CDxWindow> m_DxWindow;

	bool RegiterWndClass();
	HRESULT CreateMainWnd();
	bool Initialize();
	void Loop();
	bool ReleaseApp();
	void Update();
	void Draw();


	int m_CountFPS;
	char m_DebugStr[2048] = "aaaa";

public:
	CDxApplication();
	~CDxApplication() {};
	static LRESULT CALLBACK Grobalproc(HWND, UINT, WPARAM, LPARAM);

	int Run(HINSTANCE hInstance);

	HINSTANCE GetInstance() { return m_hinstance; }

	void GetWndClass(WNDCLASSEX* wc) {
		*wc = m_WndclassWx;
	}

	CDxWindow* GetDxWindow() { return m_DxWindow.get(); }

};

