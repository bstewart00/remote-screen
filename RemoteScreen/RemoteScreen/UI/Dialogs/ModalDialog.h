#pragma once
#ifndef MODALDIALOG_H
#define MODALDIALOG_H

#include "../Windows/Window.h"
#include "DialogControllerFactory.h"
#include "ModalDialogController.h"
#include <Windows.h>

class ModalDialog
{
public:
   ModalDialog(HINSTANCE hInst, const Window& window, int dlgResource, DLGPROC dlgProc, AbstractDialogControllerFactory* controllerFactory)
   {
      result = ::DialogBoxParam(hInst, MAKEINTRESOURCE(dlgResource), window, dlgProc, reinterpret_cast<LPARAM>(controllerFactory));
   }

   bool IsOk () const 
   { 
      return result == -1 
         ? false 
         : result != 0; 
   }

private:
   int result;
};

#endif