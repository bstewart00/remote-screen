#pragma once
#ifndef ModalDialog_H
#define ModalDialog_H

#include "Win32Framework/Window.h"
#include "../../Observable.h"
#include <Windows.h>

class ModalDialogListener
{
public:
   virtual void OnOkClicked() = 0;
   virtual void OnCancelClicked() = 0;
};

class ModalDialog : public Window<INT_PTR>, public Observable<ModalDialogListener>
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

         return window->OnInit(wParam, lParam);
      }
      return FALSE;
   }

protected:
   virtual INT_PTR OnCommand(WPARAM wParam, LPARAM lParam);
   virtual INT_PTR OnInit(WPARAM wParam, LPARAM lParam);
private:
   HINSTANCE hInstance;
   int resourceId;
   HWND parent;
};

#endif