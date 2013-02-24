#pragma once
#ifndef Window_H
#define Window_H

#include "SystemWindow.h"
#include "WindowBuilder.h"
#include <Windows.h>
#include <string>
#include <functional>
#include <cassert>
#include "../../Utils/StringConverter.h"
#include "../../WindowsException.h"
#include <memory>

template<class MessageResult = LRESULT>
class Window : public SystemWindow
{
   friend class WindowBuilder<Window>;
public:
   virtual ~Window() {}

   virtual MessageResult CALLBACK ProcessMessage(UINT msg, WPARAM wParam, LPARAM lParam)
   {
      return ::DefWindowProc(hWnd, msg, wParam, lParam);
   }

   template<class TWindow>
   static MessageResult CALLBACK InitialWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
   {
      if (msg == WM_NCCREATE) {
         LPCREATESTRUCT cs = reinterpret_cast<LPCREATESTRUCT>(lParam);
         TWindow* window = reinterpret_cast<TWindow*>(cs->lpCreateParams);
         window->hWnd = hWnd;
         window->SetLongPtr<TWindow*>(window, GWLP_USERDATA);
         window->SetLongPtr<WNDPROC>(Window::BoundWndProc<TWindow, GWLP_USERDATA>, GWLP_WNDPROC);

         return window->ProcessMessage(msg, wParam, lParam);
      } else {
         return ::DefWindowProc(hWnd, msg, wParam, lParam);
      }
   }

   template<class TWindow, int UserData>
   static MessageResult CALLBACK BoundWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
   {
      TWindow* w = Window::GetLongPtr<TWindow*>(hWnd, UserData);
      assert(w);
      return w->ProcessMessage(msg, wParam, lParam);
   }

   static MessageResult CALLBACK DefaultWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
   {
      return ::DefWindowProc(hWnd, msg, wParam, lParam);
   }

   Window<MessageResult> GetParent() const { return ::GetParent(hWnd); }

protected:
   Window(const wchar_t* classAtom = nullptr) : SystemWindow(classAtom) {}
   Window(HWND hWnd) : SystemWindow(hWnd) {}
};

#endif