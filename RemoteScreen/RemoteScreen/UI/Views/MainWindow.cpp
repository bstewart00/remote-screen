#include "MainWindow.h"
#include "../Windows/WindowFactory.h"
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
   case WM_CLOSE:
      return OnClose(wParam, lParam);
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
      break;
   case IDM_SETTINGS:
      NotifyListeners(&MainWindowListener::OnSettings);
      break;
   case IDM_EXIT:
      NotifyListeners(&MainWindowListener::OnExit);
      break;
   default:
      return Window::ProcessMessage(WM_COMMAND, wParam, lParam);
   }

   return 0;
}

LRESULT MainWindow::OnClose(WPARAM wParam, LPARAM lParam)
{
   NotifyListeners(&MainWindowListener::OnClose);
   return 0;
}

ModalDialog MainWindow::CreateAboutDialog()
{
   return ModalDialog(GetInstance(), IDD_ABOUTBOX, hWnd);
}

ApplicationSettingsDialog MainWindow::CreateApplicationSettingsDialog()
{
   return ApplicationSettingsDialog(GetInstance(), IDD_SETTINGS, hWnd);
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