#include "../../../stdafx.h"
#include "ConfigPaneController.h"

ConfigPaneController::ConfigPaneController(Window window, CREATESTRUCT* createStruct)
   : WindowController(window, createStruct)
{
}

LRESULT ConfigPaneController::ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
   switch (message) {
   case WM_NOTIFY:
      return OnNotify(wParam, lParam);
   default:
      return WindowController::ProcessMessage(message, wParam, lParam);
   }

   return 0;
}

 LRESULT ConfigPaneController::OnNotify(WPARAM wParam, LPARAM lParam)
 {
    

    return WindowController::ProcessMessage(WM_NOTIFY, wParam, lParam);
 }