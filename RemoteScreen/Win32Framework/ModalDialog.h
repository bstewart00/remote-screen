#pragma once
#ifndef ModalDialog_H
#define ModalDialog_H

#include "WindowHandle.h"
#include "WindowProcedureInitializer.h"
#include "Observable.h"
#include <Windows.h>

class ModalDialogListener
{
public:
   virtual void OnOkClicked() = 0;
   virtual void OnCancelClicked() = 0;
};

class ModalDialog : public WindowHandle, public Observable<ModalDialogListener>
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

   static INT_PTR CALLBACK InitialDlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
   {
      if (msg == WM_INITDIALOG) {
         ModalDialog* dialog = reinterpret_cast<ModalDialog*>(lParam);
         dialog->hWnd = hWnd;
         WindowProcedureInitializer<ModalDialog>::BindToWindow<DWLP_USER, DWLP_DLGPROC>(dialog);
         return dialog->OnInit(wParam, lParam);
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