#pragma once
#ifndef WindowProcedures_H
#define WindowProcedures_H

#include "WindowHandle.h"
#include <Windows.h>
#include <cassert>

class WindowProcedures
{
public:
   template<class TWindow>
   static LRESULT CALLBACK InitialWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
   {
      if (msg == WM_NCCREATE) {
         LPCREATESTRUCT cs = reinterpret_cast<LPCREATESTRUCT>(lParam);
         TWindow* window = reinterpret_cast<TWindow*>(cs->lpCreateParams);
         window->hWnd = hWnd;
         BindToWindow<TWindow, LRESULT, GWLP_USERDATA, GWLP_WNDPROC>(window);
         return window->ProcessMessage(msg, wParam, lParam);
      } else {
         return ::DefWindowProc(hWnd, msg, wParam, lParam);
      }
   }

   template<class TDialog>
   static INT_PTR CALLBACK InitialDlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
   {
      if (msg == WM_INITDIALOG) {
         TDialog* dialog = reinterpret_cast<TDialog*>(lParam);
         dialog->hWnd = hWnd;
         BindToWindow<TDialog, INT_PTR, DWLP_USER, DWLP_DLGPROC>(dialog);
         return dialog->OnInit(wParam, lParam);
      }
      return FALSE;
   }
private:
   template<class TWindow, class MessageResult, int UserDataKey, int WndProcKey>
   static void BindToWindow(TWindow* window)
   {
      auto wndProc = BoundWndProc<TWindow, MessageResult, UserDataKey>;
      window->SetLongPtr(window, UserDataKey);
      window->SetLongPtr(wndProc, WndProcKey);
   }

   template<class TWindow, class MessageResult, int UserDataKey>
   static MessageResult CALLBACK BoundWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
   {
      TWindow* w = WindowHandle::GetLongPtr<TWindow*>(hWnd, UserDataKey);
      assert(w);
      return w->ProcessMessage(msg, wParam, lParam);
   }
};

#endif