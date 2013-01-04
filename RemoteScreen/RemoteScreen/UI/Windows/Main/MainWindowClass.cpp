#include "MainWindowClass.h"

MainWindowClass::MainWindowClass(WNDPROC wndProc, std::string className, HINSTANCE hInst, int icon, int iconSmall, int menu)
   : WindowClass(wndProc, className, hInst)
{
   wndClass.style = CS_HREDRAW | CS_VREDRAW;
   wndClass.hIcon = ::LoadIcon(hInst, MAKEINTRESOURCE(icon));
   wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
   wndClass.lpszMenuName = MAKEINTRESOURCE(menu);
   wndClass.hIconSm	= ::LoadIcon(hInst, MAKEINTRESOURCE(iconSmall));
}