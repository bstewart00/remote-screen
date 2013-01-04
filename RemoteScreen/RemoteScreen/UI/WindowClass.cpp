#include "WindowClass.h"
#include <boost/nowide/convert.hpp>

WindowClass::WindowClass(WNDPROC wndProc, std::string className, HINSTANCE hInst) 
   : name(className), hInstance(hInst)
{
   wndClass.cbSize = sizeof(WNDCLASSEX);
   wndClass.style = 0;
   wndClass.lpfnWndProc	= wndProc;
   wndClass.cbClsExtra = 0;
   wndClass.cbWndExtra = 0;
   wndClass.hInstance = hInst;
   wndClass.hCursor	= ::LoadCursor(NULL, IDC_ARROW);
   wndClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
   wndClass.hIcon = nullptr;
   wndClass.lpszMenuName = nullptr;
   wndClass.hIconSm	= nullptr;
}

void WindowClass::Register()
{
   std::wstring wideClassName = boost::nowide::widen(name);
   wndClass.lpszClassName = wideClassName.c_str();
   ATOM result = ::RegisterClassEx(&wndClass);
   if (result == 0) {
      throw WindowsException("Window class registration failure.");
   }
}

HWND WindowClass::GetRunningWindow ()
{
   HWND hwnd = ::FindWindow (boost::nowide::widen(name).c_str(), 0);
   if (::IsWindow (hwnd)) {
      HWND hwndPopup = ::GetLastActivePopup(hwnd);
      if (::IsWindow (hwndPopup))
         hwnd = hwndPopup;
   }
   else {
      hwnd = 0;
   }

   return hwnd;
}