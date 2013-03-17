#pragma once
#ifndef ApplicationSettingsDialog_H
#define ApplicationSettingsDialog_H

#include "ApplicationSettingsDataBinder.h"
#include "../../Models/ApplicationSettings.h"
#include "Win32Framework/Dialogs/ModalDialog.h"
#include <Windows.h>

class ApplicationSettingsDialog : public ModalDialog, private ApplicationSettingsListener
{
public:
   ApplicationSettingsDialog(HINSTANCE hInstance, int resourceId, HWND parent);

   void BindTo(const ApplicationSettingsDataBinder& dataBinder);

private:
   void OnSettingsChanged();
   void Refresh();

   const ApplicationSettingsDataBinder* dataBinder;
   INT_PTR OnInit(WPARAM wParam, LPARAM lParam);
   INT_PTR OnCommand(WPARAM wParam, LPARAM lParam);
};

#endif