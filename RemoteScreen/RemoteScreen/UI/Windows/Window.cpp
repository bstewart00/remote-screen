#include "../../stdafx.h"
#include "Window.h"
#include "../../WindowsException.h"
#include <string>
#include <boost/nowide/convert.hpp>
#include <functional>

Window::Window(HWND hwnd) : hWnd(hwnd)
{
}

void Window::Destroy()
{
   InvokeBoolFunc(::DestroyWindow, "DestroyWindow failed");
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