#include "AboutDialogController.h"
#include "../../../resource.h"

bool AboutDialogController::OnCommand(HWND hwnd, int ctrlID, int notifyCode)
{
   if (ctrlID == IDOK || ctrlID == IDCANCEL) {
      ::EndDialog(hwnd, TRUE);
      return true;
   }
   return false;
}

bool AboutDialogController::OnNotify(HWND hwnd, int idCtrl, NMHDR *hdr)
{
   return false;
}