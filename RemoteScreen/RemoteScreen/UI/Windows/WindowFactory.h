#pragma once
#ifndef WindowFactory_H
#define WindowFactory_H

#include "Window.h"
#include "../../Utils/StringConverter.h"
#include <memory>
#include <boost/algorithm/string.hpp>

template <class TWindow>
class WindowFactory
{
public:
   WindowFactory(HINSTANCE hInstance) : hInstance(hInstance)
   {
      wndClass.cbSize = sizeof(WNDCLASSEX);
      wndClass.style = 0;
      wndClass.lpfnWndProc = Window<>::InitialWndProc<TWindow>;
      wndClass.cbClsExtra = 0;
      wndClass.cbWndExtra = sizeof(Window<>*);
      wndClass.hInstance = hInstance;
      SetSysCursor(IDC_ARROW);
      SetBgSysColor(COLOR_WINDOW);
      wndClass.hIcon = nullptr;
      wndClass.lpszMenuName = nullptr;
      wndClass.lpszClassName = nullptr;
      wndClass.hIconSm = nullptr;
   }

   std::unique_ptr<TWindow> Create(std::string className, int style, HWND parent = nullptr, std::string title = "",
      int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int width = CW_USEDEFAULT, int height = CW_USEDEFAULT, HMENU menu = nullptr)
   {
      std::wstring wideName = StringConverter::ToWide(className);

      if (!className.empty() && !IsPredefinedClass(className)) {
         wndClass.lpszClassName = wideName.c_str();
         Register();
      }

      TWindow* window = new TWindow();
      HWND hWnd = ::CreateWindowEx(
         0,
         wideName.c_str(),
         StringConverter::ToWide(title).c_str(),
         style,
         x, y, width, height,
         parent, menu, hInstance,
         window);

      if (!hWnd)
         throw WindowsException("Window creation failed.");

      return std::unique_ptr<TWindow>(window);
   }

   void SetBgSysColor(int sysColor) { wndClass.hbrBackground = reinterpret_cast<HBRUSH>(sysColor + 1); }
   void SetBgBrush(HBRUSH hbr) { wndClass.hbrBackground = hbr; }

   void SetSysCursor(const wchar_t* id) { wndClass.hCursor = ::LoadCursor(0, id); }
   void SetResCursor(const wchar_t* id) 
   { 
      HCURSOR hCur = ::LoadCursor(hInstance, id);
      wndClass.hCursor = hCur; 
   }
   void SetResIcons(int resId)
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
   void SetStyle(int flags) { wndClass.style = flags; }
   void SetMenu(int resourceId) { wndClass.lpszMenuName = MAKEINTRESOURCE(resourceId); }

private:
   bool IsPredefinedClass(std::string name)
   {
      return boost::iequals(name, "button")
         || boost::iequals(name, "combobox") 
         || boost::iequals(name, "edit")
         || boost::iequals(name, "listbox")
         || boost::iequals(name, "mdiclient")
         || boost::iequals(name, "richedit")
         || boost::iequals(name, "richedit_class")
         || boost::iequals(name, "scrollbar")
         || boost::iequals(name, "static");
   }

   void Register()
   {
      ATOM result = ::RegisterClassEx(&wndClass);
      if(result == 0) {
         throw WindowsException("Window class registration failure.");
      }
   }

   WNDCLASSEX wndClass;
   HINSTANCE hInstance;
};

#endif
