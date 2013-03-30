#pragma once
#ifndef WindowBuilder_H
#define WindowBuilder_H

#include "Window.h"
#include "../Controls/CommonControlBuilder.h"
#include "../WindowProcedures.h"
#include "Common/StringConverter.h"
#include <memory>
#include <Windows.h>

namespace Win32
{
   template <class TWindow = Window>
   class WindowBuilder : public CommonControlBuilder<TWindow>
   {
   public:
      WindowBuilder(HINSTANCE hInstance) : CommonControlBuilder(hInstance)
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

      WindowBuilder<TWindow>& ClassName(std::string className)
      {
         CommonControlBuilder::ClassName(className);
         return *this;
      }

      WindowBuilder<TWindow>& Style(int windowStyle)
      {
         CommonControlBuilder::Style(windowStyle);
         return *this;
      }

      WindowBuilder<TWindow>& Parent(HWND parent)
      {
         CommonControlBuilder::Parent(parent);
         return *this;
      }

      WindowBuilder<TWindow>& Title(std::string title)
      {
         CommonControlBuilder::Title(title);
         return *this;
      }

      WindowBuilder<TWindow>& Position(int x, int y, int width, int height)
      {
         CommonControlBuilder::Position(x, y, width, height);
         return *this;
      }

      WindowBuilder<TWindow>& Position(RECT rect)
      {
         CommonControlBuilder::Position(rect.left, rect.top, rect.right, rect.bottom);
         return *this;
      }

      WindowBuilder<TWindow>& Menu(HMENU menu)
      {
         this->menu = menu;
         return *this;
      }

      WindowBuilder<TWindow>& Id(int id)
      {
         this->menu = reinterpret_cast<HMENU>(id);
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
         std::wstring wideName = Common::StringConverter::ToWide(className);
         wndClass.lpszClassName = wideName.c_str();
         ATOM registeredClass = ::RegisterClassEx(&wndClass);
         if(registeredClass == 0) {
            throw WindowsException("Window class registration failure.");
         }

         return *this;
      }

      std::unique_ptr<TWindow> Create()
      {
         return Create(new TWindow());
      }

      template<typename T1>
      std::unique_ptr<TWindow> Create(T1&& arg1)
      {
         return Create(new TWindow(arg1));
      }

      template<typename T1, typename T2>
      std::unique_ptr<TWindow> Create(T1&& arg1, T2&& arg2)
      {
         return Create(new TWindow(arg1, arg2));
      }

      template<typename T1, typename T2, typename T3>
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
}
#endif
