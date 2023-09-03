#include <windows.h>

#include "window/pvp99window.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    pvp99window* window = new pvp99window();
    window->init();
    return 0;
}
