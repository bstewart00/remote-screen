#pragma once
#ifndef WindowProcedureInitializer_H
#define WindowProcedureInitializer_H

#include "WindowHandle.h"
#include <cassert>

template<class TWindow>
class WindowProcedureInitializer
{
public:
   template<int UserDataKey, int WndProcKey>
   static void BindToWindow(TWindow* window)
   {
      auto wndProc = BoundWndProc<UserDataKey>;

      window->SetLongPtr(window, UserDataKey);
      window->SetLongPtr(wndProc, WndProcKey);
   }

private:
   template<int UserDataKey>
   static LRESULT CALLBACK BoundWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
   {
      TWindow* w = WindowHandle::GetLongPtr<TWindow*>(hWnd, UserDataKey);
      assert(w);
      return w->ProcessMessage(msg, wParam, lParam);
   }
};

#endif