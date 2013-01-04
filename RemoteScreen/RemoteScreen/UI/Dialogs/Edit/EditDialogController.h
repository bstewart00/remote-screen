#pragma once

#include "../ModalDialogController.h"
#include "EditDialogViewModel.h"
#include "../Controls.h"
#include "../../Windows/Window.h"
#include "../../../resource.h"
#include <Windows.h>

class EditDialogController : public ModalDialogController
{
public:
   EditDialogController(HWND dialog, EditDialogViewModel* viewModel) 
      : viewModel(viewModel), 
        editControl(dialog, IDC_TESTEDIT) {}

   void OnInitDialog(HWND hwnd);
   bool OnCommand(HWND hwnd, int ctrlID, int notifyCode);
   bool OnNotify(HWND hwnd, int idCtrl, NMHDR *hdr);
private:
   Edit editControl;
   EditDialogViewModel* viewModel;
};

