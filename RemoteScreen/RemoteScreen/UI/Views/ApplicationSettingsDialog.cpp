#include "ApplicationSettingsDialog.h"

ApplicationSettingsDialog::ApplicationSettingsDialog(HINSTANCE hInstance, int resourceId, HWND parent)
   : ModalDialog(hInstance, resourceId, parent) 
{
}

void ApplicationSettingsDialog::BindTo(const ApplicationSettingsDataBinder& dataBinder)
{
   this->dataBinder = &dataBinder;
}

void ApplicationSettingsDialog::OnSomeSettingChanged() const
{
   // Get new value
}

INT_PTR ApplicationSettingsDialog::OnInit(WPARAM wParam, LPARAM lParam)
{
   // We want to populate our controls with the current values of the model here, with read-only access
   // 

   return ModalDialog::OnInit(wParam, lParam);
}

INT_PTR ApplicationSettingsDialog::OnCommand(WPARAM wParam, LPARAM lParam)
{
   return ModalDialog::OnCommand(wParam, lParam);
}