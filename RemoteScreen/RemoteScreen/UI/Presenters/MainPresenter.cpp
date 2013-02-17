#include "MainPresenter.h"
#include "../../Resource.h"
#include "../Views/ModalDialog.h"
#include "ModalDialogPresenter.h"

MainPresenter::MainPresenter(MainWindow& view, Model& model, HINSTANCE hInstance)
   : view(view), model(model), hInstance(hInstance)
{
   view.AddListener(this);
}

void MainPresenter::OnAbout() const
{
   ModalDialog dialog = view.CreateAboutDialog();
   ModalDialogPresenter presenter(dialog);
   ModalDialog::Result result = dialog.Show();
}

void MainPresenter::OnEdit() const
{
   ::MessageBox(view, L"EDIT", L"CAPT", MB_OK);

   // Get model
   // Ask view to create an edit dialog
   // View subscribes to the model for changes, then populates itself with the current values
   // Presenter created
   // Child presenter will handle Ok/close handling and make sure model is updated etc
}

void MainPresenter::OnExit() const
{
   ConfirmExit();
}

void MainPresenter::OnClose() const
{
   ConfirmExit();
}

void MainPresenter::ConfirmExit() const
{
   int result = MessageBox(view, L"Confirm exit", L"Save unsaved changes?", MB_OKCANCEL);
   if (result == IDOK)
      view.Destroy();
}