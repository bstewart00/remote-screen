#pragma once
#ifndef WindowProcedures_H
#define WindowProcedures_H

#include "WindowHandle.h"
#include <Windows.h>
#include <cassert>

class WindowProcedures
{
public:
   template<typename TWindow>
   static LRESULT CALLBACK InitialWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
   {
      return InitialMessageHandler<TWindow, LRESULT, WM_NCCREATE, GetWindow<TWindow>, DefaultWindowResult>(hWnd, msg, wParam, lParam);
   }

   template<typename TDialog>
   static INT_PTR CALLBACK InitialDlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
   {
      return InitialMessageHandler<TDialog, INT_PTR, WM_INITDIALOG, GetDialog<TDialog>, DefaultDialogResult>(hWnd, msg, wParam, lParam);
   }

private:
   template<typename T>
   static T* GetWindow(LPARAM lParam)
   {
      LPCREATESTRUCT cs = reinterpret_cast<LPCREATESTRUCT>(lParam);
      return reinterpret_cast<T*>(cs->lpCreateParams);
   }

   template<typename T>
   static T* GetDialog(LPARAM lParam)
   {
      return reinterpret_cast<T*>(lParam);
   }

   static LRESULT DefaultWindowResult(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
   {
      return ::DefWindowProc(hWnd, msg, wParam, lParam);
   }

   static INT_PTR DefaultDialogResult(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
   {
      return FALSE;
   }

   template<
      typename TWindow,
      typename MessageResult, 
      int InitialMessage, 
      TWindow*(*TWindowGetter)(LPARAM), 
      MessageResult(*DefaultHandler)(HWND, UINT, WPARAM, LPARAM)
   >
   static MessageResult CALLBACK InitialMessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
   {
      if (msg == InitialMessage) {
         TWindow* window = TWindowGetter(lParam);
         window->hWnd = hWnd;
         BindToWindow<TWindow, LRESULT, GWLP_USERDATA, GWLP_WNDPROC>(window);
         return window->ProcessMessage(msg, wParam, lParam);
      }
      return DefaultHandler(hWnd, msg, wParam, lParam);
   }

   template<typename TWindow, typename MessageResult, int UserDataKey, int WndProcKey>
   static void BindToWindow(TWindow* window)
   {
      auto wndProc = BoundWndProc<TWindow, MessageResult, UserDataKey>;
      window->SetLongPtr(window, UserDataKey);
      window->SetLongPtr(wndProc, WndProcKey);
   }

   template<typename TWindow, typename MessageResult, int UserDataKey>
   static MessageResult CALLBACK BoundWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
   {
      TWindow* w = WindowHandle::GetLongPtr<TWindow*>(hWnd, UserDataKey);
      assert(w);
      return w->ProcessMessage(msg, wParam, lParam);
   }
};

#endif