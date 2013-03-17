#pragma once
#ifndef ModalDialogPresenter_H
#define ModalDialogPresenter_H

#include "Win32Framework/Dialogs/ModalDialog.h"

class ModalDialogPresenter : private Win32::ModalDialogListener
{
public:
   ModalDialogPresenter(Win32::ModalDialog& view);

protected:
   virtual void OnOkClicked();
   virtual void OnCancelClicked();

   Win32::ModalDialog& view;
};

#endif