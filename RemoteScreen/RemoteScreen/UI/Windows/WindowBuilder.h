#pragma once
#ifndef WindowBuilder_H
#define WindowBuilder_H

#include "Window.h"
#include "SystemWindowBuilder.h"
#include "../../Utils/StringConverter.h"
#include <memory>
#include <boost/algorithm/string.hpp>
#include <Windows.h>

template <class TWindow = Window<>>
class WindowBuilder : public SystemWindowBuilder<TWindow>
{
public:
   WindowBuilder(HINSTANCE hInstance) : SystemWindowBuilder(hInstance)
   {
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
      SystemWindowBuilder::ClassName(className);
      return *this;
   }

   WindowBuilder<TWindow>& Style(int windowStyle)
   {
      SystemWindowBuilder::Style(windowStyle);
      return *this;
   }

   WindowBuilder<TWindow>& Parent(HWND parent)
   {
      SystemWindowBuilder::Parent(parent);
      return *this;
   }

   WindowBuilder<TWindow>& Title(std::string title)
   {
      SystemWindowBuilder::Title(title);
      return *this;
   }

   WindowBuilder<TWindow>& Position(int x, int y, int width, int height)
   {
      SystemWindowBuilder::Position(x, y, width, height);
      return *this;
   }

   WindowBuilder<TWindow>& Menu(HMENU menu)
   {
      this->menu = menu;
      return *this;
   }

   WindowBuilder<TWindow>& ClassStyle(int classStyle)
   {
      wndClass.style = classStyle;
      return *this;
   }

   WindowBuilder<TWindow>& ClassMenu(int resourceId)
   {
      wndClass.lpszMenuName = MAKEINTRESOURCE(resourceId);
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
      ATOM registeredClass = ::RegisterClassEx(&wndClass);
      if(registeredClass == 0) {
         throw WindowsException("Window class registration failure.");
      }

      return *this;
   }

   std::unique_ptr<TWindow> Create()
   {
      TWindow* window = new TWindow();
      HWND hWnd = ::CreateWindowEx(
         0,
         StringConverter::ToWide(className).c_str(),
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
   WNDCLASSEX wndClass;
};

#endif
