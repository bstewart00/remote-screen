#include "stdafx.h"
#include "ModalDialogPresenter.h"

ModalDialogPresenter::ModalDialogPresenter(Win32::ModalDialog& view)
   : view(view)
{
   view.AddListener(this);
}

void ModalDialogPresenter::OnOkClicked()
{
   ::EndDialog(view, TRUE);
}

void ModalDialogPresenter::OnCancelClicked()
{
   ::EndDialog(view, FALSE);
}