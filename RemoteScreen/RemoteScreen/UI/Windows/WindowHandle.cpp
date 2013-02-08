#include "../../stdafx.h"
#include "WindowHandle.h"
#include "../../WindowsException.h"
#include <string>
#include <boost/nowide/convert.hpp>
#include <functional>

WindowHandle::WindowHandle(HWND hwnd) : hWnd(hwnd)
{
}

void WindowHandle::Destroy()
{
   InvokeBoolFunc(::DestroyWindow, "DestroyWindow failed");
}

void WindowHandle::Show(int nCmdShow)
{
   ::ShowWindow(hWnd, nCmdShow);
   InvokeBoolFunc(::UpdateWindow, "UpdateWindow failed");
}

void WindowHandle::InvokeBoolFunc(std::function<BOOL(HWND)> func, std::string errorMessage)
{
   BOOL result = func(hWnd);
   if (result == 0) {
      throw WindowsException(errorMessage);
   }
}