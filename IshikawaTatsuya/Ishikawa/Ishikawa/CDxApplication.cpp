#include "CDxApplication.h"
#include "CDxWindow.h"
#include <time.h>

CDxApplication *pApp = nullptr;


CDxApplication::CDxApplication()
{
	pApp = this;
}

LRESULT CDxApplication::GrobalWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (pApp) {
		pApp->GetDxWindow()->LocalWndProc(hwnd, msg, wParam, lParam);
	}
	return S_OK;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(lpCmdLine);		// 無くても良いけど、警告が出る（未使用宣言）
	
	CDxApplication a;

	pApp->Run(hInstance);

	return 0;
}

int CDxApplication::Run(HINSTANCE hInstance)
{
	m_hInstance = hInstance;
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
	HRESULT hr = m_DxWindow->RegisterWindowClass(&m_WndClassWx);
	return hr;
}

bool CDxApplication::CreateMainWnd()
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

	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	MSG msg;

	// フレームカウント初期化
	timeBeginPeriod(1);	// 分解能を設定
	dwExecLastTime = dwFPSLastTime = timeGetTime();	// システム時刻をミリ秒単位で取得
	dwCurrentTime = dwFrameCount = 0;


	// メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳と送出
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwFPSLastTime) >= 1000)	// 1秒ごとに実行
			{
#ifdef _DEBUG
				m_CountFPS = dwFrameCount;
#endif
				dwFPSLastTime = dwCurrentTime;				// FPSを測定した時刻を保存
				dwFrameCount = 0;							// カウントをクリア
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))	// 1/60秒ごとに実行
			{
				dwExecLastTime = dwCurrentTime;	// 処理した時刻を保存

#ifdef _DEBUG	// デバッグ版の時だけFPSを表示する
				wsprintf(m_DebugStr, WINDOW_NAME);
				wsprintf(&m_DebugStr[strlen(m_DebugStr)], " FPS:%d", m_CountFPS);
				SetWindowText(m_DxWindow->GetHWND(), m_DebugStr);
#endif

				Update();			// 更新処理
				Draw();				// 描画処理

				//CheckScene();

				dwFrameCount++;
			}
		}
	}
}

void CDxApplication::ReleaseApp()
{
}

void CDxApplication::Update()
{
}

void CDxApplication::Draw()
{
}
