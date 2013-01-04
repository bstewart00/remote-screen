#pragma once
#ifndef ABOUTDIALOGCONTROLLER_H
#define ABOUTDIALOGCONTROLLER_H

#include "../ModalDialogController.h"
#include <Windows.h>

class AboutDialogController : public ModalDialogController
{
public:
   AboutDialogController(HWND dialog, nullptr_t* viewModel) {}

   void OnInitDialog(HWND hwnd) {}
   bool OnCommand(HWND hwnd, int ctrlID, int notifyCode);
   bool OnNotify(HWND hwnd, int idCtrl, NMHDR *hdr);
};

#endif