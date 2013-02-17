#pragma once
#ifndef ModalDialogPresenter_H
#define ModalDialogPresenter_H

#include "../Views/ModalDialog.h"

class ModalDialogPresenter
{
public:
   ModalDialogPresenter(const ModalDialog& dialog);

private:
   const ModalDialog& dialog;
};

#endif