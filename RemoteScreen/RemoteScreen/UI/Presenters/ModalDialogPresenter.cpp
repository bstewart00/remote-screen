#include "ModalDialogPresenter.h"

ModalDialogPresenter::ModalDialogPresenter(ModalDialog& view)
   : view(view)
{
   view.AddListener(this);
}

void ModalDialogPresenter::OnOkClicked() const
{
   ::EndDialog(view, TRUE);
}

void ModalDialogPresenter::OnCancelClicked() const
{
   ::EndDialog(view, FALSE);
}