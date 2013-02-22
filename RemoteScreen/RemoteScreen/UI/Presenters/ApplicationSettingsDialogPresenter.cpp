#include "ApplicationSettingsDialogPresenter.h"

ApplicationSettingsDialogPresenter::ApplicationSettingsDialogPresenter(ApplicationSettingsDialog& view, ApplicationSettings& model)
   : ModalDialogPresenter(view), model(model), dataBinder(ApplicationSettingsDataBinder(view, model))
{
   view.BindTo(dataBinder);
}