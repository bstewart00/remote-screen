#pragma once
#ifndef ApplicationSettingsDialogPresenter_H
#define ApplicationSettingsDialogPresenter_H

#include "../../Models/ApplicationSettings.h"
#include "../Views/ApplicationSettingsDialog.h"
#include "ModalDialogPresenter.h"

class ApplicationSettingsDialogPresenter : public ModalDialogPresenter
{
public:
   ApplicationSettingsDialogPresenter(ApplicationSettingsDialog& view, ApplicationSettings& model);
private:
   const ApplicationSettingsDataBinder dataBinder;
   ApplicationSettings& model;
};

#endif