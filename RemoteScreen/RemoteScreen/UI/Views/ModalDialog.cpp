#include "ModalDialog.h"

ModalDialog::ModalDialog(HINSTANCE hInstance, int resourceId, HWND parent)
   : hInstance(hInstance), resourceId(resourceId), parent(parent)
{
}

ModalDialog::Result ModalDialog::Show()
{
   INT_PTR result = ::DialogBoxParam(hInstance, MAKEINTRESOURCE(resourceId), parent, ModalDialog::InitialDlgProc<ModalDialog>, reinterpret_cast<LPARAM>(this));
   return static_cast<Result>(result);
}

INT_PTR CALLBACK ModalDialog::ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
   switch (message) {
   case WM_COMMAND:
      return OnCommand(wParam, lParam);
   }

   return FALSE;
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