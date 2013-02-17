#pragma once
#ifndef ModalDialogPresenter_H
#define ModalDialogPresenter_H

#include "../Views/ModalDialog.h"

class ModalDialogPresenter
{
public:
   ModalDialogPresenter(const ModalDialog2& dialog);

private:
   const ModalDialog2& dialog;
};

#endif