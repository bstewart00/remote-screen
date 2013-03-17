#include "stdafx.h"
#include "MainPresenter.h"
#include "../../Resource.h"
#include "../Views/ApplicationSettingsDialog.h"
#include "../Presenters/ApplicationSettingsDialogPresenter.h"
#include "ModalDialogPresenter.h"
#include "../../Models/ApplicationSettings.h"

MainPresenter::MainPresenter(MainWindow& view, ApplicationSettings& settings, HINSTANCE hInstance)
   : view(view), settings(settings), hInstance(hInstance)
{
   view.AddListener(this);
}

void MainPresenter::OnAbout()
{
   Win32::ModalDialog dialog = view.CreateAboutDialog();
   ModalDialogPresenter presenter(dialog);

   Win32::ModalDialog::Result result = dialog.Show();
}

void MainPresenter::OnSettings()
{
   ApplicationSettingsDialog dialog = view.CreateApplicationSettingsDialog();
   ApplicationSettingsDialogPresenter presenter(dialog, settings);
   Win32::ModalDialog::Result result = dialog.Show();

   if (result == Win32::ModalDialog::Result::Ok) {
      // Persist app settings
   }
}

void MainPresenter::OnExit()
{
   ConfirmExit();
}

void MainPresenter::OnClose()
{
   ConfirmExit();
}

void MainPresenter::OnCreated()
{

}

void MainPresenter::ConfirmExit() const
{
   int result = ::MessageBox(view, L"Confirm exit", L"Save unsaved changes?", MB_OKCANCEL);
   if (result == IDOK)
      view.Destroy();
}