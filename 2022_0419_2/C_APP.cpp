#include "C_APP.h"
#include"C_Window.h"
#include<time.h>
App* pApp = nullptr;
App::App() //未使用
{
	pApp = this;
}


LRESULT App::GrobalProc(HWND hwnd, UINT msg, WPARAM wPalam, LPARAM lPalam)
{
	//if (pApp)
	//{
	//	pApp->GetWindow()->LocalWndProc(hwnd, msg, wPalam, lPalam);
	//}
	return S_OK;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	//無くてもいいけど、警告が出る
	UNREFERENCED_PARAMETER(lpCmdLine);		//無くてもいいけど、警告が出る

	App a;
	pApp->Run(hInstance);
    return 0;
}

int App::Run(HINSTANCE hInstance)
{
	m_hInstance = hInstance;
	m_Window = std::make_unique<Window>(hInstance);
	if (!RegistarWndClass())
	{
		return -1;
	}
	if (!CreateMainWnd())
	{
		return -1;
	}
	if (!Initialize())
	{
		return -1;
	}
	Loop();
	RegistarWndClass();
	return 0;
}

bool App::RegistarWndClass()
{
	HRESULT hr = m_Window->RegisterWindowClass(&m_WndClassWx);
	return hr;
}

bool App::CreateMainWnd()
{
	HRESULT hr= m_Window->CreateMainWindow();
	return hr;
}

bool App::Initialize()
{
	//DXの設定
	return 1;
}

void App::Loop()
{
    srand((unsigned int)time(NULL));

    DWORD dwExecLastTime;
    DWORD dwFPSLastTime;
    DWORD dwCurrentTime;
    DWORD dwFrameCount;

    MSG msg;

    // フレームカウント初期化
    timeBeginPeriod(1);    // 分解能を設定
    dwExecLastTime = dwFPSLastTime = timeGetTime();    // システム時刻をミリ秒単位で取得
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

            if ((dwCurrentTime - dwFPSLastTime) >= 1000)    // 1秒ごとに実行
            {
#ifdef _DEBUG
                m_CountFPS = dwFrameCount;
#endif
                dwFPSLastTime = dwCurrentTime;                // FPSを測定した時刻を保存
                dwFrameCount = 0;                            // カウントをクリア
            }

            if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))    // 1/60秒ごとに実行
            {
                dwExecLastTime = dwCurrentTime;    // 処理した時刻を保存

#ifdef _DEBUG    // デバッグ版の時だけFPSを表示する
            //    wsprintf(m_DebugStr, WINDOW_NAME);
                //wsprintf(&m_DebugStr[strlen(m_DebugStr)], " FPS:%d", m_CountFPS);
                SetWindowText(m_Window->GetHWND(), m_DebugStr);
#endif

                Update();            // 更新処理
                Draw();                // 描画処理

                //CheckScene();

                dwFrameCount++;
            }
        }
    }
}

void App::ReleaseApp()
{
}

void App::Update()
{
}

void App::Draw()
{
}
