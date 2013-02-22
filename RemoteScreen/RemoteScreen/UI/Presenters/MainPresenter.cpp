#include "MainPresenter.h"
#include "../../Resource.h"
#include "../Views/ApplicationSettingsDialog.h"
#include "../Presenters/ApplicationSettingsDialogPresenter.h"
#include "ModalDialogPresenter.h"
#include "../../Models/ApplicationSettings.h"

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
   ApplicationSettings settings;
   ApplicationSettingsDialog dialog = view.CreateApplicationSettingsDialog();
   ApplicationSettingsDialogPresenter presenter(dialog, settings);

   ModalDialog::Result result = dialog.Show();
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
   int result = ::MessageBox(view, L"Confirm exit", L"Save unsaved changes?", MB_OKCANCEL);
   if (result == IDOK)
      view.Destroy();
}