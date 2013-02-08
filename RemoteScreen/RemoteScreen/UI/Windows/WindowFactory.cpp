#include "../../stdafx.h"
#include "WindowFactory.h"
#include "WindowController.h"
#include "../../WindowsException.h"
#include "../../Utils/StringConverter.h"

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

WindowHandle WindowFactory::Create()
{

   std::unique_ptr<std::wstring> className = StringConverter::ToWide(wndClass.GetName());
   std::unique_ptr<std::wstring> windowTitle = StringConverter::ToWide(titleCaption);
 
   hWnd = ::CreateWindowEx(
      0,
      className.get()->c_str(),
      windowTitle.get()->c_str(),
      style,
      x, y, width, height,
      hWndParent, hMenu, wndClass.GetInstance(),
      nullptr);

   if (!hWnd)
      throw WindowsException("WindowHandle creation failed.");

   return WindowHandle(hWnd);
}

WindowHandle WindowFactory::Create(HINSTANCE hInstance)
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

   return WindowHandle(hWnd);
}

WindowHandle WindowFactory::CreateChild(const WindowHandle& parent, const WindowClass wndClass)
{
   WindowFactory factory(wndClass);
   factory.AddStyle(WS_CHILD | WS_VISIBLE);
   factory.SetParent(parent);
   return factory.Create();
}

WindowHandle WindowFactory::CreateDefaultChild(const WindowHandle& parent, std::string className, HINSTANCE hInstance)
{
   WindowClass childClass(WindowController::DefaultWndProc, className, hInstance);
   childClass.Register();

   return CreateChild(parent, childClass);
}
