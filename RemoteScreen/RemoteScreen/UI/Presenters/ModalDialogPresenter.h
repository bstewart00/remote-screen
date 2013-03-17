#pragma once
#ifndef ModalDialogPresenter_H
#define ModalDialogPresenter_H

#include "Win32Framework/Dialogs/ModalDialog.h"

class ModalDialogPresenter : private ModalDialogListener
{
public:
   ModalDialogPresenter(ModalDialog& view);

protected:
   virtual void OnOkClicked();
   virtual void OnCancelClicked();

   ModalDialog& view;
};

#endif