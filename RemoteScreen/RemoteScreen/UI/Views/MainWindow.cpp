#include "MainWindow.h"
#include "../Windows/WindowFactory.h"
#include "../Dialogs/About/AboutDialogController.h"
#include "../Dialogs/Edit/EditDialogController.h"
#include "../Dialogs/ModalDialog.h"
#include "../Dialogs/ModalDialogController.h"
#include "../../CustomMessages.h"
#include "../../Utils/StringResource.h"
#include "../../Resource.h"
#include <algorithm>
#include <functional>

std::unique_ptr<MainWindow> MainWindow::Create(HINSTANCE hInstance)
{
   WindowFactory<MainWindow> factory(hInstance);
   factory.SetStyle(CS_HREDRAW | CS_VREDRAW);
   factory.SetMenu(IDC_REMOTESCREEN);
   factory.SetResIcons(IDI_REMOTESCREEN);
   return factory.Create(StringResource(IDC_REMOTESCREEN), WS_OVERLAPPEDWINDOW | WS_VISIBLE, nullptr, StringResource(IDS_APP_TITLE));
}

LRESULT CALLBACK MainWindow::ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
   switch (message) {
   case WM_CREATE:
      OnCreate();
      break;
   case WM_COMMAND:
      return OnCommand(wParam, lParam);
   case WM_SIZE:
      OnSize(LOWORD(lParam), HIWORD(lParam));
      break;
   case MSG_MOVESPLITTER:
      MoveSplitter(wParam);
      break;
   case WM_DESTROY:
      ::PostQuitMessage(0);
      break;
   }

   return Window::ProcessMessage(message, wParam, lParam);
}

void MainWindow::OnCreate()
{
   HINSTANCE hInstance = GetInstance();

   //leftWin = ConfigPane::Create(window, hInstance);
   //rightWin = ContentPane::Create(window, hInstance);
   //splitter = Splitter::RegisterAndCreate(window, hInstance);
}

LRESULT MainWindow::OnCommand(WPARAM wParam, LPARAM lParam)
{
   int wmId = LOWORD(wParam);
   int wmEvent = HIWORD(wParam);
   switch (wmId) {
   case IDM_ABOUT: 
      NotifyListeners(&MainWindowListener::OnAbout);
      ShowAboutDialog();
      break;
   case IDM_EDIT:
      NotifyListeners(&MainWindowListener::OnEdit);
      ShowEditDialog();
      break;
   case IDM_EXIT:
      NotifyListeners(&MainWindowListener::OnExit);
      Destroy();
      break;
   default:
      return Window::ProcessMessage(WM_COMMAND, wParam, lParam);
   }

   return 0;
}

void MainWindow::ShowAboutDialog()
{
   HINSTANCE hInst = GetLongPtr<HINSTANCE>(GWLP_HINSTANCE);
   DialogControllerFactory<AboutDialogController, nullptr_t> factory(nullptr);
   ModalDialog dialog(hInst, *this, IDD_ABOUTBOX, ModalDialogController::DialogProc, &factory);
}

void MainWindow::ShowEditDialog()
{
   HINSTANCE hInst = GetLongPtr<HINSTANCE>(GWLP_HINSTANCE);
   EditDialogViewModel viewModel("TEST");
   DialogControllerFactory<EditDialogController, EditDialogViewModel> factory(&viewModel);
   ModalDialog dialog(hInst, *this, IDD_EDIT, ModalDialogController::DialogProc, &factory);
}

void MainWindow::OnSize(int cx, int cy) 
{
   //this->cx = cx;
   //this->cy = cy;
   //int xSplit = (this->cx * splitRatioPercentage) / 100;
   //if (xSplit < 0)
   //   xSplit = 0;
   //splitter.MoveDelayPaint (xSplit, 0, splitterWidth, this->cy);
   //leftWin->Move (0, 0, xSplit, this->cy);
   //rightWin->Move (xSplit + splitterWidth, 0, this->cx - xSplit - splitterWidth, this->cy);

   //splitter.ForceRepaint ();
}

void MainWindow::MoveSplitter (int x)
{
   //splitRatioPercentage = x * 100 / cx;
   //if (splitRatioPercentage < 0)
   //   splitRatioPercentage = 0;
   //else if (splitRatioPercentage > 100)
   //   splitRatioPercentage = 100;
   //Size (cx, cy);
}