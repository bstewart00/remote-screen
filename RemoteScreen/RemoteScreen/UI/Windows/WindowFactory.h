#pragma once
#ifndef WINDOWFACTORY_H
#define WINDOWFACTORY_H

#include "Window.h"

class WindowFactory
{
public:
   WindowFactory(HINSTANCE hInstance);

   Window Create(std::string className, int style, HWND parent = nullptr, std::string title = "",
      int x = 0, int y = 0, int width = CW_USEDEFAULT, int height = CW_USEDEFAULT, HMENU menu = nullptr);
   Window CreateDefaultChild(const Window& parent, std::string className);

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
   void SetClassName(std::string name) { className = name; }
   void SetWndProc(WNDPROC wndProc) { wndClass.lpfnWndProc = wndProc; }

private:
   void Register();

   std::string className;
   WNDCLASSEX wndClass;
   HINSTANCE hInstance;
};

#endif
