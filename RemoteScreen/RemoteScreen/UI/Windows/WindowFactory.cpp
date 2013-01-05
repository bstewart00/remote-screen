#include "WindowFactory.h"
#include "../../WindowsException.h"
#include <boost/nowide/convert.hpp>

WindowFactory::WindowFactory(const WindowClass& wndClass)
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

void WindowFactory::SetPosition (int x, int y, int width, int height)
{
    x = x;
    y = y;
    width = width;
    height = height;
}

Window WindowFactory::Create()
{
   std::wstring className = boost::nowide::widen(wndClass.GetName());
   std::wstring windowTitle = boost::nowide::widen(titleCaption);
 
   hWnd = ::CreateWindowEx(
      0,
      className.c_str(),
      windowTitle.c_str(),
      style,
      x, y, width, height,
      hWndParent, hMenu, wndClass.GetInstance(),
      nullptr);

   if (!hWnd)
      throw WindowsException("WindowFactory creation failed");

   return Window(hWnd);
}

MainWindowFactory::MainWindowFactory(const WindowClass& wndClass, std::string title)
   : WindowFactory(wndClass)
{
   SetTitle(title);
   style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
}

ChildWindowFactory::ChildWindowFactory(const WindowClass& wndClass, Window parent)
   : WindowFactory(wndClass)
{
   style = WS_CHILD;
   hWndParent = parent;
}
