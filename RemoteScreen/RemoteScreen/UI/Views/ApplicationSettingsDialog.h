#pragma once
#ifndef ApplicationSettingsDialog_H
#define ApplicationSettingsDialog_H

#include "../../Models/ApplicationSettings.h"
#include "ModalDialog.h"

class ApplicationSettingsDialog;

class ApplicationSettingsDataBinder
{
public:
   ApplicationSettingsDataBinder(ApplicationSettingsDialog& view, ApplicationSettings& model)
      : view(view), model(model)
   {
   }

   const ApplicationSettingsDialog& view;
   const ApplicationSettings& model;
};

class ApplicationSettingsDialog : public ModalDialog, private ApplicationSettingsListener
{
public:
   ApplicationSettingsDialog(HINSTANCE hInstance, int resourceId, HWND parent);

   void BindTo(const ApplicationSettingsDataBinder& dataBinder);

private:
   void OnSomeSettingChanged() const;

   const ApplicationSettingsDataBinder* dataBinder;
   INT_PTR OnInit(WPARAM wParam, LPARAM lParam);
   INT_PTR OnCommand(WPARAM wParam, LPARAM lParam);
};

#endif