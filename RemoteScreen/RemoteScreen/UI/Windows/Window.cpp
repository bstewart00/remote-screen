#include "Window.h"
#include "../../WindowsException.h"
#include <string>
#include <boost/nowide/convert.hpp>
#include <Windows.h>
#include <functional>

Window::Window(const WindowClass& wndClass)
    : wndClass(wndClass),
      hWnd(nullptr),
      exStyle(0),
      style(WS_OVERLAPPED),
      x(CW_USEDEFAULT),
      y(0),
      width(CW_USEDEFAULT),
      height(0),
      hWndParent(nullptr),
      hMenu(nullptr)
{
}

void Window::Create()
{
   std::wstring className = boost::nowide::widen(wndClass.GetName());
   std::wstring windowName = boost::nowide::widen(name);

   hWnd = ::CreateWindowEx(
      0,
      className.c_str(),
      windowName.c_str(),
      style,
      x, y, width, height,
      hWndParent, hMenu, wndClass.GetInstance(),
      this);

   if (!hWnd)
      throw WindowsException("Window creation failed");
}

void Window::Destroy()
{
   InvokeBoolFunc(::DestroyWindow, "UpdateWindow failed");
}

void Window::Show(int nCmdShow)
{
   ::ShowWindow(hWnd, nCmdShow);
   InvokeBoolFunc(::UpdateWindow, "UpdateWindow failed");
}

void Window::InvokeBoolFunc(std::function<BOOL(HWND)> func, std::string errorMessage)
{
   BOOL result = func(hWnd);
   if (result == 0) {
      throw WindowsException(errorMessage);
   }
}