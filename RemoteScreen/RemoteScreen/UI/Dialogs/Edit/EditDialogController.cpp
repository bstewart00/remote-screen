#include "../../../stdafx.h"
#include "EditDialogController.h"
#include "../../../resource.h"
#include <array>

void EditDialogController::OnInitDialog(HWND hwnd)
{
   editControl.SetString(viewModel->text);
}
bool EditDialogController::OnCommand(HWND hwnd, int ctrlID, int notifyCode)
{
   switch (ctrlID)
    {
    case IDOK:
       std::array<wchar_t, 50> buf;
       editControl.GetString(buf.data(), buf.size());
       viewModel->text = boost::nowide::narrow(buf.data());

        if (viewModel->IsNameOk()) {
            ::EndDialog(hwnd, TRUE);
        }
        else {
            ::MessageBox(hwnd, L"Please, enter valid name", L"Name Editor", MB_ICONINFORMATION | MB_OK);
        }
        return true;
    case IDCANCEL:
        ::EndDialog(hwnd, FALSE);
        return true;
    }
    return false;
}
bool EditDialogController::OnNotify(HWND hwnd, int idCtrl, NMHDR *hdr)
{
   return false;
}