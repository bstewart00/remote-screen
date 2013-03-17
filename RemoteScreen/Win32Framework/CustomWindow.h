#pragma once
#ifndef CustomWindow_H
#define CustomWindow_H

#include "WindowProcedureInitializer.h"
#include "CustomWindowBuilder.h"
#include "WindowHandle.h"
#include <Windows.h>
#include <string>
#include <functional>
#include <cassert>
#include "Utils/StringConverter.h"
#include "WindowsException.h"
#include <memory>

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
         window->hWnd = hWnd;
         WindowProcedureInitializer<CustomWindow>::BindToWindow<GWLP_USERDATA, GWLP_WNDPROC>(window);
         return window->ProcessMessage(msg, wParam, lParam);
      } else {
         return ::DefWindowProc(hWnd, msg, wParam, lParam);
      }
   }

protected:
   CustomWindow() : WindowHandle() {}
};

#endif