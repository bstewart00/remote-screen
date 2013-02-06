#pragma once
#ifndef DIALOGCONTROLLERFACTORY_H
#define DIALOGCONTROLLERFACTORY_H

class ModalDialogController;

class AbstractDialogControllerFactory
{
public:
   AbstractDialogControllerFactory (void* viewModel) : viewModel (viewModel) {}
   virtual ModalDialogController* MakeController (HWND hwndDlg) = 0;
protected:
   void* viewModel;
};

template <class Controller, class ViewModel>
class DialogControllerFactory : public AbstractDialogControllerFactory
{
public:
   DialogControllerFactory (void* viewModel) : AbstractDialogControllerFactory(viewModel) {}

   ModalDialogController* MakeController (HWND hwndDlg)
   {
      return new Controller (hwndDlg, reinterpret_cast<ViewModel*>(viewModel));
   }
};

#endif