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
      parent = nullptr;
      className = "";
      title = "";
      x = CW_USEDEFAULT;
      y = CW_USEDEFAULT;
      width = CW_USEDEFAULT;
      height = CW_USEDEFAULT;
      windowStyle = 0;
      menu = nullptr;

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

   WindowFactory<TWindow>& ClassName(std::string className)
   {
      this->className = className;
      return *this;
   }

   WindowFactory<TWindow>& ClassStyle(int classStyle)
   {
      wndClass.style = classStyle;
      return *this;
   }

   WindowFactory<TWindow>& Style(int windowStyle)
   {
      this->windowStyle = windowStyle;
      return *this;
   }

   WindowFactory<TWindow>& Parent(HWND parent)
   {
      this->parent = parent;
      return *this;
   }

   WindowFactory<TWindow>& Title(std::string title)
   {
      this->title = title;
      return *this;
   }

   WindowFactory<TWindow>& Position(int x, int y, int width, int height)
   {
      this->x = x;
      this->y = y;
      this->width = width;
      this->height = height;
      return *this;
   }

   WindowFactory<TWindow>& ClassMenu(int resourceId)
   {
      wndClass.lpszMenuName = MAKEINTRESOURCE(resourceId);
      return *this;
   }

   WindowFactory<TWindow>& Menu(HMENU menu)
   {
      this->menu = menu;
      return *this;
   }

   WindowFactory<TWindow>& Background(int systemColor)
   {
      wndClass.hbrBackground = reinterpret_cast<HBRUSH>(systemColor + 1);
      return *this;
   }

   WindowFactory<TWindow>& Background(HBRUSH brush)
   {
      wndClass.hbrBackground = brush;
      return *this;
   }

   WindowFactory<TWindow>& CursorFromSystem(const wchar_t* predefinedId)
   {
      wndClass.hCursor = ::LoadCursor(nullptr, predefinedId);
      return *this;
   }

   WindowFactory<TWindow>& CursorFromResource(const wchar_t* resId)
   {
      wndClass.hCursor = ::LoadCursor(hInstance, resId);
      return *this;
   }

   WindowFactory<TWindow>& Icon(int resId)
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

   std::unique_ptr<TWindow> Create()
   {
      std::wstring wideName = StringConverter::ToWide(className);

      ATOM registeredClass = 0;
      if (!className.empty() && !IsPredefinedClass(className)) {
         wndClass.lpszClassName = wideName.c_str();
         registeredClass = Register();
      }

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

   ATOM Register()
   {
      ATOM result = ::RegisterClassEx(&wndClass);
      if(result == 0) {
         throw WindowsException("Window class registration failure.");
      }

      return result;
   }

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
