#include "CDxApplication.h"
#include "CDxWindow.h"
#include <time.h>

CDxApplication* pApp = nullptr;

CDxApplication::CDxApplication()
{
	pApp = this;
}

LRESULT CDxApplication::Grobalproc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM IParam)
{
	if (pApp) {
		pApp->GetDxWindow()->LocalWndProc(hwnd, msg, wParam, IParam);
	}
	return S_OK;
}

int CDxApplication::Run(HINSTANCE hInstance)
{
	m_hinstance = hInstance;
	m_DxWindow = std::make_unique<CDxWindow>(hInstance);

	if (!RegiterWndClass()) {
		return -1;
	}

	if (!CreateMainWnd()) {
		return -1;
	}

	if (!Initialize()) {
		return -1;
	}

	Loop();

	ReleaseApp();

	return 0;
}

bool CDxApplication::RegiterWndClass()
{
	HRESULT hr = m_DxWindow->RegisterWindowClass(&m_WndclassWx);
	return hr;
}

HRESULT CDxApplication::CreateMainWnd()
{
	HRESULT hr = m_DxWindow->CreateMainWindow();
	return 1;
}

bool CDxApplication::Initialize()
{
	//DXの設定
	return 1;
}

void CDxApplication::Loop()
{
	srand((unsigned int)time(NULL));

	DWORD dwExcLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	MSG msg;

	//フレームカウント初期化
	timeBeginPeriod(1); //分解能
	dwExcLastTime = dwFPSLastTime = timeGetTime();
	dwCurrentTime = dwFrameCount = 0;


	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{//PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				//メッセージの翻訳と送出
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		else
		{
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwFPSLastTime) >= 1000 / 60)
			{
				dwExcLastTime = dwCurrentTime;	//処理した時刻保存

#ifdef _DEBUG //デバッグ版の時だけFPSを表示する
				wsprintf(m_DebugStr, WINDOW_NAME);
				wsprintf(&m_DebugStr[strlen(m_DebugStr)],"FPS:%d", m_CountFPS);
				SetWindowText(m_DxWindow->GetHWND(), m_DebugStr);


#endif // _DEBUG
				Update();
				Draw();

				//ChackScene();

				dwFrameCount++;
			}
		}

	}
}

bool CDxApplication::ReleaseApp()
{
	return false;
}

void CDxApplication::Update()
{
}

void CDxApplication::Draw()
{
}
