#include "pvp99window.h"

pvp99window::pvp99window()
{
    hwnd = nullptr;
    hInstance = nullptr;
    screen_width = 800;
    screen_height = 600;
}

void pvp99window::init()
{
    WNDCLASSEX wc;
    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = L"PvP99WindowClass";

    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, L"Window class registration failed!", L"Error", MB_OK | MB_ICONERROR);
        return;
    }

    hwnd = CreateWindowEx(NULL, L"PvP99WindowClass", L"pvp99", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, screen_width, screen_height, NULL, NULL, GetModuleHandle(NULL), this);

    if (!hwnd)
    {
        MessageBox(NULL, L"Window creation failed!", L"Error", MB_OK | MB_ICONERROR);
        return;
    }

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    renderer::get_instance().init(hwnd, hInstance);

    run();
}

void pvp99window::run()
{
    MSG msg;

    while (true)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                break;
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            InvalidateRect(hwnd, NULL, TRUE);
            UpdateWindow(hwnd);
            
            Sleep(010);

            renderer::get_instance().update(0.0f);
            renderer::get_instance().render();
        }
    }
}

LRESULT CALLBACK pvp99window::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    switch (msg)
    {
    case WM_PAINT:
        PAINTSTRUCT ps;
        hdc = BeginPaint(hwnd, &ps);
        EndPaint(hwnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}