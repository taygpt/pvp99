#ifndef PVP99WINDOW_H
#define PVP99WINDOW_H

#include <windows.h>

#include "../gfx/renderer.h"

class pvp99window {
public:
    pvp99window();

    void init();
private:
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    void run();

    HWND hwnd;
    HINSTANCE hInstance;

    uint16_t screen_width;
    uint16_t screen_height;
};

#endif // PVP99WINDOW_H