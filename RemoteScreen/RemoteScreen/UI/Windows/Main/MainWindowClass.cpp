#include "MainWindowClass.h"

MainWindowClass::MainWindowClass(WNDPROC wndProc, std::string className, HINSTANCE hInst, int icon, int menu)
   : WindowClass(wndProc, className, hInst)
{
   SetSizeRedraw();
   SetResIcons(icon);
   wndClass.lpszMenuName = MAKEINTRESOURCE(menu);
}