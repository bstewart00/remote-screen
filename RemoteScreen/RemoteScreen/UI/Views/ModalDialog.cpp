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