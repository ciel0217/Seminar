#include "C_APP.h"
#include"C_Window.h"
#include<time.h>
App* pApp = nullptr;
App::App() //���g�p
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
	UNREFERENCED_PARAMETER(hPrevInstance);	//�����Ă��������ǁA�x�����o��
	UNREFERENCED_PARAMETER(lpCmdLine);		//�����Ă��������ǁA�x�����o��

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
	//DX�̐ݒ�
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

    // �t���[���J�E���g������
    timeBeginPeriod(1);    // ����\��ݒ�
    dwExecLastTime = dwFPSLastTime = timeGetTime();    // �V�X�e���������~���b�P�ʂŎ擾
    dwCurrentTime = dwFrameCount = 0;


    // ���b�Z�[�W���[�v
    while (1)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
                break;
            }
            else
            {
                // ���b�Z�[�W�̖|��Ƒ��o
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            dwCurrentTime = timeGetTime();

            if ((dwCurrentTime - dwFPSLastTime) >= 1000)    // 1�b���ƂɎ��s
            {
#ifdef _DEBUG
                m_CountFPS = dwFrameCount;
#endif
                dwFPSLastTime = dwCurrentTime;                // FPS�𑪒肵��������ۑ�
                dwFrameCount = 0;                            // �J�E���g���N���A
            }

            if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))    // 1/60�b���ƂɎ��s
            {
                dwExecLastTime = dwCurrentTime;    // ��������������ۑ�

#ifdef _DEBUG    // �f�o�b�O�ł̎�����FPS��\������
            //    wsprintf(m_DebugStr, WINDOW_NAME);
                //wsprintf(&m_DebugStr[strlen(m_DebugStr)], " FPS:%d", m_CountFPS);
                SetWindowText(m_Window->GetHWND(), m_DebugStr);
#endif

                Update();            // �X�V����
                Draw();                // �`�揈��

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
