#pragma once
#ifndef WindowBuilder_H
#define WindowBuilder_H

#include "Window.h"
#include "../../Utils/StringConverter.h"
#include <memory>
#include <boost/algorithm/string.hpp>

template <class TWindow>
class WindowBuilder
{
public:
   WindowBuilder(HINSTANCE hInstance) : hInstance(hInstance)
   {
      parent = nullptr;
      className = "";
      title = "";
      x = CW_USEDEFAULT;
      y = CW_USEDEFAULT;
      width = CW_USEDEFAULT;
      height = CW_USEDEFAULT;
      windowStyle = 0;
      menu = nullptr;
      registeredClass = 0;

      wndClass.cbSize = sizeof(WNDCLASSEX);
      wndClass.style = 0;
      wndClass.lpfnWndProc = Window<>::InitialWndProc<TWindow>;
      wndClass.cbClsExtra = 0;
      wndClass.cbWndExtra = sizeof(Window<>*);
      wndClass.hInstance = hInstance;
      CursorFromSystem(IDC_ARROW);
      Background(COLOR_WINDOW);
      wndClass.hIcon = nullptr;
      wndClass.lpszMenuName = nullptr;
      wndClass.lpszClassName = nullptr;
      wndClass.hIconSm = nullptr;
   }

   WindowBuilder<TWindow>& ClassName(std::string className)
   {
      this->className = className;
      return *this;
   }

   WindowBuilder<TWindow>& ClassName(const wchar_t* systemClassName)
   {
      return ClassName(StringConverter::ToUtf8(systemClassName));
   }

   WindowBuilder<TWindow>& ClassStyle(int classStyle)
   {
      wndClass.style = classStyle;
      return *this;
   }

   WindowBuilder<TWindow>& Style(int windowStyle)
   {
      this->windowStyle = windowStyle;
      return *this;
   }

   WindowBuilder<TWindow>& Parent(HWND parent)
   {
      this->parent = parent;
      return *this;
   }

   WindowBuilder<TWindow>& Title(std::string title)
   {
      this->title = title;
      return *this;
   }

   WindowBuilder<TWindow>& Position(int x, int y, int width, int height)
   {
      this->x = x;
      this->y = y;
      this->width = width;
      this->height = height;
      return *this;
   }

   WindowBuilder<TWindow>& ClassMenu(int resourceId)
   {
      wndClass.lpszMenuName = MAKEINTRESOURCE(resourceId);
      return *this;
   }

   WindowBuilder<TWindow>& Menu(HMENU menu)
   {
      this->menu = menu;
      return *this;
   }

   WindowBuilder<TWindow>& Background(int systemColor)
   {
      wndClass.hbrBackground = reinterpret_cast<HBRUSH>(systemColor + 1);
      return *this;
   }

   WindowBuilder<TWindow>& Background(HBRUSH brush)
   {
      wndClass.hbrBackground = brush;
      return *this;
   }

   WindowBuilder<TWindow>& CursorFromSystem(const wchar_t* predefinedId)
   {
      wndClass.hCursor = ::LoadCursor(nullptr, predefinedId);
      return *this;
   }

   WindowBuilder<TWindow>& CursorFromResource(const wchar_t* resId)
   {
      wndClass.hCursor = ::LoadCursor(hInstance, resId);
      return *this;
   }

   WindowBuilder<TWindow>& Icon(int resId)
   {
      wndClass.hIcon = ::LoadIcon(hInstance, MAKEINTRESOURCE (resId));
      wndClass.hIconSm =(HICON)::LoadImage(
         hInstance, 
         MAKEINTRESOURCE(resId), 
         IMAGE_ICON, 
         ::GetSystemMetrics(SM_CXSMICON),
         ::GetSystemMetrics(SM_CYSMICON),
         LR_SHARED);

      return *this;
   }

   WindowBuilder<TWindow>& Register()
   {
      std::wstring wideName = StringConverter::ToWide(className);
      wndClass.lpszClassName = wideName.c_str();
      registeredClass = ::RegisterClassEx(&wndClass);
      if(registeredClass == 0) {
         throw WindowsException("Window class registration failure.");
      }

      return *this;
   }

   std::unique_ptr<TWindow> Create()
   {
      std::wstring wideName = StringConverter::ToWide(className);
      const wchar_t* classNameOrAtom =  registeredClass != 0 ? MAKEINTATOM(registeredClass) : wideName.c_str();

      TWindow* window = new TWindow(classNameOrAtom);
      HWND hWnd = ::CreateWindowEx(
         0,
         classNameOrAtom,
         StringConverter::ToWide(title).c_str(),
         windowStyle,
         x, y, width, height,
         parent, menu, hInstance,
         window);

      if (!hWnd)
         throw WindowsException("Window creation failed.");

      return std::unique_ptr<TWindow>(window);
   }

   std::unique_ptr<TWindow> Create2()
   {
      std::wstring wideName = StringConverter::ToWide(className);
      const wchar_t* classNameOrAtom = wideName.c_str();

      TWindow* window = new TWindow(classNameOrAtom);
      HWND hWnd = ::CreateWindowEx(
         0,
         wideName.c_str(),
         StringConverter::ToWide(title).c_str(),
         windowStyle,
         x, y, width, height,
         parent, menu, hInstance,
         nullptr);

      window->hWnd = hWnd;

      if (!hWnd)
         throw WindowsException("Window creation failed.");

      return std::unique_ptr<TWindow>(window);
   }

private:
   ATOM registeredClass;
   std::string className;
   std::string title;
   int windowStyle;
   int x;
   int y;
   int width;
   int height;
   HWND parent;
   HMENU menu;

   WNDCLASSEX wndClass;
   HINSTANCE hInstance;
};

#endif
