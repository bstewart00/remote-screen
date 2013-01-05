#include "MainWindowController.h"
#include "../../Dialogs/ModalDialog.h"
#include "../../Dialogs/DialogControllerFactory.h"
#include "../../Dialogs/About/AboutDialogController.h"
#include "../../Dialogs/Edit/EditDialogController.h"
#include "../../../Resource.h"

MainWindowController::MainWindowController(Window window)
   : WindowController(window)
{
}

LRESULT MainWindowController::ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
   int wmId, wmEvent;
   PAINTSTRUCT ps;
   HDC hdc;

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
   case WM_PAINT:
      hdc = ::BeginPaint(window, &ps);
      TextOut(hdc, 0, 0, L"Test", 4);
      ::EndPaint(window, &ps);
      break;
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