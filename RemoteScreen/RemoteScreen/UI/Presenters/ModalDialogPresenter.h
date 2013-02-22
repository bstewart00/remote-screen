#pragma once
#ifndef ModalDialogPresenter_H
#define ModalDialogPresenter_H

#include "../Views/ModalDialog.h"

class ModalDialogPresenter : private ModalDialogListener
{
public:
   ModalDialogPresenter(ModalDialog& view);

protected:
   void OnOkClicked() const;
   void OnCancelClicked() const;

   ModalDialog& view;
};

#endif