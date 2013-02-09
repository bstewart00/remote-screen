#include "../../stdafx.h"
#include "WindowFactory.h"
#include "WindowController.h"
#include "../../WindowsException.h"
#include "../../Utils/StringConverter.h"

WindowFactory::WindowFactory(HINSTANCE hInstance) : hInstance(hInstance)
{
   wndClass.cbSize = sizeof(WNDCLASSEX);
   wndClass.style = 0;
   wndClass.lpfnWndProc	= nullptr;
   wndClass.cbClsExtra = 0;
   wndClass.cbWndExtra = 0;
   wndClass.hInstance = hInstance;
   SetSysCursor(IDC_ARROW);
   SetBgSysColor(COLOR_WINDOW);
   wndClass.hIcon = nullptr;
   wndClass.lpszMenuName = nullptr;
   wndClass.lpszClassName = nullptr;
   wndClass.hIconSm = nullptr;
}

void WindowFactory::Register()
{
   if (!wndClass.lpfnWndProc)
      wndClass.lpfnWndProc = WindowController::DefaultWndProc;

   std::unique_ptr<std::wstring> wideClassName = StringConverter::ToWide(className);
   wndClass.lpszClassName = wideClassName.get()->c_str();
   ATOM result = ::RegisterClassEx(&wndClass);
   if(result == 0) {
      throw WindowsException("WindowHandle class registration failure.");
   }
}

WindowHandle WindowFactory::Create(std::string className, int style, HWND parent, std::string title, int x, int y, int width, int height, HMENU menu)
{
   if (!className.empty())
      Register();

   std::unique_ptr<std::wstring> wideName = StringConverter::ToWide(className);
   std::unique_ptr<std::wstring> wideTitle = StringConverter::ToWide(title);

   HWND hWnd = ::CreateWindowEx(
      0,
      wideName.get()->c_str(),
      wideTitle.get()->c_str(),
      style,
      x, y, width, height,
      parent, menu, hInstance,
      nullptr);

   if (!hWnd)
      throw WindowsException("WindowHandle creation failed.");

   return WindowHandle(hWnd);
}

WindowHandle WindowFactory::CreateDefaultChild(const WindowHandle& parent, std::string className)
{
   SetWndProc(WindowController::DefaultWndProc);
   SetClassName(className);
   return Create(className, WS_CHILD | WS_VISIBLE, parent);
}
