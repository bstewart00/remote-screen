#include "stdafx.h"
#include "ApplicationSettingsDialog.h"

ApplicationSettingsDialog::ApplicationSettingsDialog(HINSTANCE hInstance, int resourceId, HWND parent)
   : ModalDialog(hInstance, resourceId, parent) 
{
}

void ApplicationSettingsDialog::BindTo(const ApplicationSettingsDataBinder& dataBinder)
{
   this->dataBinder = &dataBinder;
}

void ApplicationSettingsDialog::OnSettingsChanged()
{
   Refresh();
}

void ApplicationSettingsDialog::Refresh()
{
   int newValue = dataBinder->model.someSetting();
   //update UI
}

INT_PTR ApplicationSettingsDialog::OnInit(WPARAM wParam, LPARAM lParam)
{
   Refresh();
   return ModalDialog::OnInit(wParam, lParam);
}

INT_PTR ApplicationSettingsDialog::OnCommand(WPARAM wParam, LPARAM lParam)
{
   return ModalDialog::OnCommand(wParam, lParam);
}