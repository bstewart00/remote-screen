#pragma once
#ifndef ModalDialog_H
#define ModalDialog_H

#include <Windows.h>

enum class ModalDialogResult
{
   Cancel = 0,
   Ok = 1
};

class ModalDialog2
{
public:
   ModalDialog2(HINSTANCE hInstance, int resourceId, HWND parent);
   ModalDialogResult Show();

   template<class TWindow>
   static LRESULT CALLBACK InitialDlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
   {
      if (msg == WM_INITDIALOG) {
         TWindow* dialog = reinterpret_cast<TDialog*>(lParam);
         dialog->hWnd = hWnd;
         dialog->SetLongPtr<TWindow*>(window, DWLP_USER);
         dialog->SetLongPtr<DLGPROC>(Window::BoundWndProc<TWindow, DWLP_DLGPROC>, DWLP_DLGPROC);

         return dialog->ProcessMessage(msg, wParam, lParam);
      }
      return FALSE;
   }

private:
   HINSTANCE hInstance;
   int resourceId;
   HWND parent;
};

#endif