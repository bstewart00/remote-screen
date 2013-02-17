#pragma once
#ifndef ModalDialog_H
#define ModalDialog_H

#include "../Windows/Window.h"
#include <Windows.h>

class ModalDialog : public Window<INT_PTR>
{
public:
   enum class Result
   {
      Cancel = 0,
      Ok = 1
   };

   ModalDialog(HINSTANCE hInstance, int resourceId, HWND parent);
   ModalDialog::Result Show();

   INT_PTR CALLBACK ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);

   template<class TWindow>
   static INT_PTR CALLBACK InitialDlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
   {
      if (msg == WM_INITDIALOG) {
         TWindow* window = reinterpret_cast<TWindow*>(lParam);
         window->hWnd = hWnd;
         window->SetLongPtr<TWindow*>(window, DWLP_USER);
         window->SetLongPtr<DLGPROC>(Window::BoundWndProc<TWindow, DWLP_USER>, DWLP_DLGPROC);

         return window->ProcessMessage(msg, wParam, lParam);
      }
      return FALSE;
   }

    static INT_PTR CALLBACK DefaultDlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
       return ::DefDlgProc(hWnd, msg, wParam, lParam);
    }

private:
   INT_PTR OnCommand(WPARAM wParam, LPARAM lParam);

   HINSTANCE hInstance;
   int resourceId;
   HWND parent;
};

#endif