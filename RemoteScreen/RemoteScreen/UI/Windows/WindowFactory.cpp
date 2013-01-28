#include "WindowFactory.h"
#include "WindowController.h"
#include "../../WindowsException.h"
#include <boost/nowide/convert.hpp>

WindowFactory::WindowFactory(const WindowClass wndClass)
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
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
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
      throw WindowsException("Window creation failed.");

   return Window(hWnd);
}

Window WindowFactory::Create(HINSTANCE hInstance)
{
   std::wstring className = boost::nowide::widen(wndClass.GetName());
   std::wstring windowTitle = boost::nowide::widen(titleCaption);
 
   hWnd = ::CreateWindowEx(
      0,
      className.c_str(),
      windowTitle.c_str(),
      style,
      x, y, width, height,
      hWndParent, hMenu, hInstance,
      nullptr);

   if (!hWnd)
      throw WindowsException("WindowFactory creation failed");

   return Window(hWnd);
}

Window WindowFactory::CreateChild(const Window& parent, const WindowClass wndClass)
{
   WindowFactory factory(wndClass);
   factory.AddStyle(WS_CHILD | WS_VISIBLE);
   factory.SetParent(parent);
   return factory.Create();
}

Window WindowFactory::CreateDefaultChild(const Window& parent, std::string className, HINSTANCE hInstance)
{
   WindowClass childClass(WindowController::DefaultWndProc, className, hInstance);
   childClass.Register();

   return CreateChild(parent, childClass);
}
