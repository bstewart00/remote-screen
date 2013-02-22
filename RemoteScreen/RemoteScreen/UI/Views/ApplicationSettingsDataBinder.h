#pragma once
#ifndef ApplicationSettingsDataBinder_H
#define ApplicationSettingsDataBinder_H

#include "../../Models/ApplicationSettings.h"
#include "ApplicationSettingsDialog.h"

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

#endif