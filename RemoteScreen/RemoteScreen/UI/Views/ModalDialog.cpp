#include "ModalDialog.h"

ModalDialog2::ModalDialog2(HINSTANCE hInstance, int resourceId, HWND parent)
   : hInstance(hInstance), resourceId(resourceId), parent(parent)
{
}

ModalDialogResult ModalDialog2::Show()
{
   auto result = ::DialogBoxParam(hInstance, MAKEINTRESOURCE(resourceId), parent, nullptr, 0);

   return ModalDialogResult::Ok;
}