#include "ModalDialog.h"
#include "../WindowProcedures.h"

namespace Win32
{
   ModalDialog::ModalDialog(HINSTANCE hInstance, int resourceId, HWND parent)
      : hInstance(hInstance), resourceId(resourceId), parent(parent)
   {
   }

   ModalDialog::Result ModalDialog::Show()
   {
      INT_PTR result = ::DialogBoxParam(hInstance, MAKEINTRESOURCE(resourceId), parent, WindowProcedures::InitialDlgProc<ModalDialog>, reinterpret_cast<LPARAM>(this));
      return static_cast<Result>(result);
   }

   INT_PTR CALLBACK ModalDialog::ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam)
   {
      switch (message) {
      case WM_INITDIALOG:
         return OnInit(wParam, lParam);
      case WM_COMMAND:
         return OnCommand(wParam, lParam);
      }

      return FALSE;
   }

   INT_PTR ModalDialog::OnInit(WPARAM wParam, LPARAM lParam)
   {
      return TRUE;
   }

   INT_PTR ModalDialog::OnCommand(WPARAM wParam, LPARAM lParam)
   {
      switch (LOWORD(wParam)) 
      { 
      case IDOK:
         NotifyListeners(&ModalDialogListener::OnOkClicked);
         return TRUE;
      case IDCANCEL:
         NotifyListeners(&ModalDialogListener::OnCancelClicked);
         return TRUE;
      } 
      return FALSE;
   }
}