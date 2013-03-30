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
	// Ask view to create config pane
	// Create config pane presenter as private unique ptr member

	// Ask view to create content pane
	// Create content pane presenter as private unique ptr member

	// Bind content pane as listener to view
	// This feels wrong. The presenter is supposed to drive the view.
	/*
	ContentPane triggers MonitorChanged
	ContentPanePresenter listens to it, it may reject the event, but it notifies the parent
	MainWindowPresenter::MonitorChanged
	The main window presenter responds to this by getting the new monitor from the config pane, and triggering an event on the
	ContentPanePresenter -> DisplayMonitor(monitor)

	*/
}

void MainPresenter::ConfirmExit() const
{
   int result = ::MessageBox(view, L"Confirm exit", L"Save unsaved changes?", MB_OKCANCEL);
   if (result == IDOK)
      view.Destroy();
}