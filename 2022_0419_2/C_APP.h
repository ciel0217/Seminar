#pragma once
#include"main.h"
#include<memory>
class Window;
class App {
private:
	HINSTANCE m_hInstance;
	WNDCLASSEX m_WndClassWx;

	std::unique_ptr<Window>m_Window;

	bool RegistarWndClass();
	bool CreateMainWnd();
	bool Initialize();
	void Loop();
	void ReleaseApp();
	void Update();
	void Draw();

	int m_CountFPS;
	char m_DebugStr[2048] = "aaaa";

public:
	App();
	~App(){}
	static LRESULT CALLBACK GrobalProc(HWND, UINT, WPARAM, LPARAM);

	int Run(HINSTANCE hInstance);
	HINSTANCE GetHInstance() { return m_hInstance; }
	void GetWndClass(WNDCLASSEX* wc) {
		*wc = m_WndClassWx;
	}
	Window* GetWindow() { return m_Window.get(); }
};
