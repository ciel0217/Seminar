#include "C_Window.h"
#include "C_APP.h"
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

HRESULT Window::RegisterWindowClass(WNDCLASSEX* wnd)
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
        (HBRUSH)(COLOR_WINDOW + 1),
        NULL,
        APP_NAME,
        NULL
    };
    HRESULT hr;
    hr = RegisterClassEx(&m_wndClass);
    *wnd = m_wndClass;
    return hr;
}

HRESULT Window::CreateMainWindow()
{
    m_hWnd = CreateWindow(APP_NAME, WINDOW_NAME,
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
    if (!m_hWnd)
    {
        return FALSE;
    }
    ShowWindow(m_hWnd, SW_SHOW);//m_hWndÇSW_SHOWÇÃèÛë‘Ç…ê›íËÇ∑ÇÈ
    UpdateWindow(m_hWnd);//ShowWindow()ÇÃê›íËÇ≈ï\é¶Ç∑ÇÈ

    return 1;
}

LRESULT  LocalWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)//ñ¢égóp
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
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return 1;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return 1;
}
