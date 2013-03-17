#pragma once
#ifndef CustomWindowBuilder_H
#define CustomWindowBuilder_H

#include "CustomWindow.h"
#include "CommonControlBuilder.h"
#include "WindowProcedures.h"
#include "Utils/StringConverter.h"
#include <memory>
#include <boost/algorithm/string.hpp>
#include <Windows.h>

template <class TWindow = CustomWindow>
class CustomWindowBuilder : public CommonControlBuilder<TWindow>
{
public:
   CustomWindowBuilder(HINSTANCE hInstance) : CommonControlBuilder(hInstance)
   {
      wndClass.cbSize = sizeof(WNDCLASSEX);
      wndClass.style = 0;
      wndClass.lpfnWndProc = WindowProcedures::InitialWndProc<TWindow>;
      wndClass.cbClsExtra = 0;
      wndClass.cbWndExtra = sizeof(TWindow*);
      wndClass.hInstance = hInstance;
      CursorFromSystem(IDC_ARROW);
      Background(COLOR_WINDOW);
      wndClass.hIcon = nullptr;
      wndClass.lpszMenuName = nullptr;
      wndClass.lpszClassName = nullptr;
      wndClass.hIconSm = nullptr;
   }

   CustomWindowBuilder<TWindow>& ClassName(std::string className)
   {
      CommonControlBuilder::ClassName(className);
      return *this;
   }

   CustomWindowBuilder<TWindow>& Style(int windowStyle)
   {
      CommonControlBuilder::Style(windowStyle);
      return *this;
   }

   CustomWindowBuilder<TWindow>& Parent(HWND parent)
   {
      CommonControlBuilder::Parent(parent);
      return *this;
   }

   CustomWindowBuilder<TWindow>& Title(std::string title)
   {
      CommonControlBuilder::Title(title);
      return *this;
   }

   CustomWindowBuilder<TWindow>& Position(int x, int y, int width, int height)
   {
      CommonControlBuilder::Position(x, y, width, height);
      return *this;
   }

   CustomWindowBuilder<TWindow>& Position(RECT rect)
   {
      CommonControlBuilder::Position(rect.left, rect.top, rect.right, rect.bottom);
      return *this;
   }

   CustomWindowBuilder<TWindow>& Menu(HMENU menu)
   {
      this->menu = menu;
      return *this;
   }

   CustomWindowBuilder<TWindow>& Id(int id)
   {
      this->menu = reinterpret_cast<HMENU>(id);
      return *this;
   }

   CustomWindowBuilder<TWindow>& ClassStyle(int classStyle)
   {
      wndClass.style = classStyle;
      return *this;
   }

   CustomWindowBuilder<TWindow>& ClassMenu(int resourceId)
   {
      wndClass.lpszMenuName = MAKEINTRESOURCE(resourceId);
      return *this;
   }

   CustomWindowBuilder<TWindow>& Background(int systemColor)
   {
      wndClass.hbrBackground = reinterpret_cast<HBRUSH>(systemColor + 1);
      return *this;
   }

   CustomWindowBuilder<TWindow>& Background(HBRUSH brush)
   {
      wndClass.hbrBackground = brush;
      return *this;
   }

   CustomWindowBuilder<TWindow>& CursorFromSystem(const wchar_t* predefinedId)
   {
      wndClass.hCursor = ::LoadCursor(nullptr, predefinedId);
      return *this;
   }

   CustomWindowBuilder<TWindow>& CursorFromResource(const wchar_t* resId)
   {
      wndClass.hCursor = ::LoadCursor(hInstance, resId);
      return *this;
   }

   CustomWindowBuilder<TWindow>& Icon(int resId)
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

   CustomWindowBuilder<TWindow>& Register()
   {
      std::wstring wideName = StringConverter::ToWide(className);
      wndClass.lpszClassName = wideName.c_str();
      ATOM registeredClass = ::RegisterClassEx(&wndClass);
      if(registeredClass == 0) {
         throw WindowsException("CustomWindow class registration failure.");
      }

      return *this;
   }

   std::unique_ptr<TWindow> Create()
   {
      return Create(new TWindow());
   }

   template<class T1>
   std::unique_ptr<TWindow> Create(T1&& arg1)
   {
      return Create(new TWindow(arg1));
   }

   template<class T1, class T2>
   std::unique_ptr<TWindow> Create(T1&& arg1, T2&& arg2)
   {
      return Create(new TWindow(arg1, arg2));
   }

   template<class T1, class T2, class T3>
   std::unique_ptr<TWindow> Create(T1&& arg1, T2&& arg2, T3&& arg3)
   {
      return Create(new TWindow(arg1, arg2, arg3));
   }

private:
   std::unique_ptr<TWindow> Create(TWindow* window)
   {
      CreateWindowHandle(window);
      return std::unique_ptr<TWindow>(window);
   }

   WNDCLASSEX wndClass;
};

#endif
