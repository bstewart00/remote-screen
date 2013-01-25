#include "WindowClass.h"
#include <boost/nowide/convert.hpp>

WindowClass::WindowClass(std::string className, HINSTANCE hInst)
   : name(className), hInstance(hInst)
{
   Construct(nullptr);
}

WindowClass::WindowClass(WNDPROC wndProc, std::string className, HINSTANCE hInst) 
   : name(className), hInstance(hInst)
{
   Construct(wndProc);
}

void WindowClass::Construct(WNDPROC wndProc)
{
   wndClass.cbSize = sizeof(WNDCLASSEX);
   wndClass.style = 0;
   wndClass.lpfnWndProc	= wndProc;
   wndClass.cbClsExtra = 0;
   wndClass.cbWndExtra = 0;
   wndClass.hInstance = hInstance;
   SetSysCursor(IDC_ARROW);
   SetBgSysColor(COLOR_WINDOW);
   wndClass.hIcon = nullptr;
   wndClass.lpszMenuName = nullptr;
   wndClass.hIconSm	= nullptr;
}

void WindowClass::Register()
{
   std::wstring wideClassName = boost::nowide::widen(name);
   wndClass.lpszClassName = wideClassName.c_str();
   ATOM result = ::RegisterClassEx(&wndClass);
   if(result == 0) {
      throw WindowsException("Window class registration failure.");
   }
}

HWND WindowClass::GetRunningWindow() const
{
   HWND hwnd = ::FindWindow(boost::nowide::widen(name).c_str(), 0);
   if(::IsWindow (hwnd)) {
      HWND hwndPopup = ::GetLastActivePopup(hwnd);
      if(::IsWindow (hwndPopup))
         hwnd = hwndPopup;
   }
   else {
      hwnd = 0;
   }

   return hwnd;
}

void WindowClass::SetResIcons(int resId)
{
   wndClass.hIcon = ::LoadIcon(hInstance, MAKEINTRESOURCE (resId));
   wndClass.hIconSm =(HICON)::LoadImage(
      hInstance, 
      MAKEINTRESOURCE(resId), 
      IMAGE_ICON, 
      ::GetSystemMetrics(SM_CXSMICON),
      ::GetSystemMetrics(SM_CYSMICON),
      LR_SHARED);
}