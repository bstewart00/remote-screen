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
   ModalDialogResult result = dialog.Show();
}

void MainPresenter::OnEdit() const
{
   ::MessageBox(view, L"EDIT", L"CAPT", MB_OK);
}

void MainPresenter::OnExit() const
{
   ::MessageBox(view, L"EXIT", L"CAPT", MB_OK);
   view.Destroy();
}
