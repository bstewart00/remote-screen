#include "ModalDialog.h"

ModalDialog::ModalDialog(HINSTANCE hInstance, int resourceId, HWND parent)
   : hInstance(hInstance), resourceId(resourceId), parent(parent)
{
}

ModalDialog::Result ModalDialog::Show()
{
   auto result = ::DialogBoxParam(hInstance, MAKEINTRESOURCE(resourceId), parent, nullptr, 0);

   return Result::Ok;
}