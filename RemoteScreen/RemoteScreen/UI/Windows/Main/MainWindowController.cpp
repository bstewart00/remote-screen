#include "../../Controls/TreeView/TreeView.h"
#include "MainWindowController.h"
#include "../WindowFactory.h"
#include "../../Dialogs/ModalDialog.h"
#include "../../Dialogs/DialogControllerFactory.h"
#include "../../Dialogs/About/AboutDialogController.h"
#include "../../Dialogs/Edit/EditDialogController.h"
#include "../../Controls/Splitter/Controller.h"
#include "../../Controls/Splitter/Splitter.h"
#include "../../Controls/TreeView/TreeView.h"
#include "../ContentPane/ContentPane.h"
#include "../ConfigPane/ConfigPane.h"
#include "../../../Resource.h"
#include "../../../CustomMessages.h"
#include "../../../StringResource.h"

MainWindowController::MainWindowController(Window window, CREATESTRUCT* createStruct)
   : WindowController(window, createStruct),
   leftWin(nullptr),
   rightWin(nullptr),
   splitter(nullptr),
   splitRatioPercentage(30)
{
   HINSTANCE hInstance = window.GetInstance();

   leftWin = ConfigPane(window, hInstance);
   rightWin = ContentPane(window, hInstance);
   splitter = Splitter::RegisterAndCreate(window, hInstance);
}

LRESULT MainWindowController::ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
   int wmId, wmEvent;

   switch (message) {
   case WM_COMMAND:
      wmId = LOWORD(wParam);
      wmEvent = HIWORD(wParam);
      switch (wmId) {
      case IDM_ABOUT: 
         ShowAboutDialog();
         break;
      case IDM_EDIT:
         ShowEditDialog();
         break;
      case IDM_EXIT:
         window.Destroy();
         break;
      default:
         return WindowController::ProcessMessage(message, wParam, lParam);
      }
      break;
   case WM_SIZE:
      Size (LOWORD(lParam), HIWORD(lParam));
      return 0;
   case MSG_MOVESPLITTER:
      MoveSplitter (wParam);
      return 0;
   case WM_DESTROY:
      ::PostQuitMessage(0);
      break;
   default:
      return WindowController::ProcessMessage(message, wParam, lParam);
   }

   return 0;
}

void MainWindowController::ShowAboutDialog()
{
   HINSTANCE hInst = window.GetLongPtr<HINSTANCE>(GWLP_HINSTANCE);
   DialogControllerFactory<AboutDialogController, nullptr_t> factory(nullptr);
   ModalDialog dialog(hInst, window, IDD_ABOUTBOX, ModalDialogController::DialogProc, &factory);
}

void MainWindowController::ShowEditDialog()
{
   HINSTANCE hInst = window.GetLongPtr<HINSTANCE>(GWLP_HINSTANCE);
   EditDialogViewModel viewModel("TEST");
   DialogControllerFactory<EditDialogController, EditDialogViewModel> factory(&viewModel);
   ModalDialog dialog(hInst, window, IDD_EDIT, ModalDialogController::DialogProc, &factory);
}

void MainWindowController::Size (int cx, int cy) 
{
   this->cx = cx;
   this->cy = cy;
   int xSplit = (this->cx * splitRatioPercentage) / 100;
   if (xSplit < 0)
      xSplit = 0;
   splitter.MoveDelayPaint (xSplit, 0, splitterWidth, this->cy);
   leftWin.Move (0, 0, xSplit, this->cy);
   rightWin.Move (xSplit + splitterWidth, 0, this->cx - xSplit - splitterWidth, this->cy);

   splitter.ForceRepaint ();
}


void MainWindowController::MoveSplitter (int x)
{
   splitRatioPercentage = x * 100 / cx;
   if (splitRatioPercentage < 0)
      splitRatioPercentage = 0;
   else if (splitRatioPercentage > 100)
      splitRatioPercentage = 100;
   Size (cx, cy);
}