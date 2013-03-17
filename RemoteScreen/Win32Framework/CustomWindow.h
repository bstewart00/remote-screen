#pragma once
#ifndef CustomWindow_H
#define CustomWindow_H

#include "CustomWindowBuilder.h"
#include "WindowHandle.h"
#include <Windows.h>
#include <string>
#include <functional>
#include <cassert>
#include "Utils/StringConverter.h"
#include "WindowsException.h"
#include <memory>

template<class TWindow, int UserDataKey, int WndProcKey>
void InitializeWindow(TWindow window, HWND hWnd)
{
   window->hWnd = hWnd;
   window->SetLongPtr(this, UserDataKey);
   window->SetLongPtr(BoundWndProc, WndProcKey);
}

template<class TWindow, int UserDataKey>
LRESULT CALLBACK BoundWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
   TWindow* w = WindowHandle::GetLongPtr<TWindow*>(hWnd, UserDataKey);
   assert(w);
   return w->ProcessMessage(msg, wParam, lParam);
}

class CustomWindow : public WindowHandle
{
   friend class CustomWindowBuilder<CustomWindow>;
public:
   virtual ~CustomWindow() {}

   virtual LRESULT CALLBACK ProcessMessage(UINT msg, WPARAM wParam, LPARAM lParam)
   {
      return ::DefWindowProc(hWnd, msg, wParam, lParam);
   }

   static LRESULT CALLBACK InitialWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
   {
      if (msg == WM_NCCREATE) {
         LPCREATESTRUCT cs = reinterpret_cast<LPCREATESTRUCT>(lParam);
         CustomWindow* window = reinterpret_cast<CustomWindow*>(cs->lpCreateParams);
         window->Initialize(hWnd);
         return window->ProcessMessage(msg, wParam, lParam);
      } else {
         return ::DefWindowProc(hWnd, msg, wParam, lParam);
      }
   }

protected:
   CustomWindow() : WindowHandle() {}

   void Initialize(HWND hWnd)
   {
      this->hWnd = hWnd;
      this->SetLongPtr(this, GWLP_USERDATA);
      this->SetLongPtr(CustomWindow::BoundWndProc, GWLP_WNDPROC);
   }

   static LRESULT CALLBACK BoundWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
   {
      CustomWindow* w = WindowHandle::GetLongPtr<CustomWindow*>(hWnd, GWLP_USERDATA);
      assert(w);
      return w->ProcessMessage(msg, wParam, lParam);
   }
};

#endif