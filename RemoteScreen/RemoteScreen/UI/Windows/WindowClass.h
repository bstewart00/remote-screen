#pragma once
#ifndef WINDOWCLASS_H
#define WINDOWCLASS_H

#include "../../Utils/StringResource.h"
#include "../../WindowsException.h"
#include "Window.h"
#include <string>

class WindowClass
{
public:
   WindowClass(std::string name, HINSTANCE hInst);
   WindowClass(WNDPROC wndProc, std::string name, HINSTANCE hInst);

   void Register();
   std::string GetName() const { return name; }
   HINSTANCE GetInstance() const { return hInstance; }

   void SetBgSysColor(int sysColor)
   {
      wndClass.hbrBackground = reinterpret_cast<HBRUSH>(sysColor + 1);
   }

   void SetBgBrush(HBRUSH hbr)
   {
      wndClass.hbrBackground = hbr;
   }

   void SetSysCursor(const wchar_t* id) 
   {
      wndClass.hCursor = ::LoadCursor(0, id); 
   }
   void SetResCursor(const wchar_t* id) 
   { 
      HCURSOR hCur = ::LoadCursor(hInstance, id);
      wndClass.hCursor = hCur; 
   }
   void SetResIcons(int resId);
   void SetDblClicks()
   {
      wndClass.style |= CS_DBLCLKS;
   }
   void SetSizeRedraw()
   {
      wndClass.style |=(CS_HREDRAW | CS_VREDRAW);
   }

   void SetMenu(int resourceId) 
   {
      wndClass.lpszMenuName = MAKEINTRESOURCE(resourceId);
   }

protected:
   std::string name;
   WNDCLASSEX wndClass;
   HINSTANCE hInstance;

private:
   void Construct(WNDPROC wndProc);
};

#endif
