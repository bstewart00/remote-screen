#pragma once
#ifndef ModalDialog_H
#define ModalDialog_H

#include "../Windows/Window.h"
#include <Windows.h>

class ModalDialog : public Window
{
public:
   enum class Result
   {
      Cancel = 0,
      Ok = 1
   };

   ModalDialog(HINSTANCE hInstance, int resourceId, HWND parent);
   ModalDialog::Result Show();

   template<class TWindow>
   static INT_PTR CALLBACK InitialDlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
   {
      if (msg == WM_INITDIALOG) {
         TWindow* window = reinterpret_cast<TWindow*>(lParam);
         window->hWnd = hWnd;
         window->SetLongPtr<TWindow*>(window, DWLP_USER);
         window->SetLongPtr<DLGPROC>(Window::BoundWndProc<TWindow, DWLP_DLGPROC, INT_PTR>, DWLP_DLGPROC);

         return window->ProcessMessage(msg, wParam, lParam);
      }
      return FALSE;
   }

private:
   HINSTANCE hInstance;
   int resourceId;
   HWND parent;
};

#endif