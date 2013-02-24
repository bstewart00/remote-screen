#include "../../stdafx.h"
#include "MainWindow.h"
#include "ContentPane.h"
#include "Splitter.h"
#include "../Windows/WindowBuilder.h"
#include "../../CustomMessages.h"
#include "../../Utils/StringResource.h"
#include "../../Resource.h"
#include "ConfigPane.h"
#include <algorithm>
#include <functional>

std::unique_ptr<MainWindow> MainWindow::Create(HINSTANCE hInstance)
{
   return WindowBuilder<MainWindow>(hInstance)
      .ClassName(StringResource(IDC_REMOTESCREEN))
      .ClassStyle(CS_HREDRAW | CS_VREDRAW)
      .ClassMenu(IDC_REMOTESCREEN)
      .Style(WS_OVERLAPPEDWINDOW)
      .Icon(IDI_REMOTESCREEN)
      .Title(StringResource(IDS_APP_TITLE))
      .Register()
      .Create();
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
   case WM_CLOSE:
      return OnClose(wParam, lParam);
   }

   return Window::ProcessMessage(message, wParam, lParam);
}

void MainWindow::OnCreate()
{
   HINSTANCE hInstance = GetInstance();

   std::unique_ptr<Window> leftWin = ConfigPane::Create(hInstance, *this);
   std::unique_ptr<Window> rightWin = ContentPane::Create(hInstance, *this);
   splitWindow = SplitWindow::Create(hInstance, *this, std::move(leftWin), std::move(rightWin), 30);
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
   case WM_SIZE:
      OnSize(LOWORD(lParam), HIWORD(lParam));
      return 0;
   }

   return Window::ProcessMessage(WM_COMMAND, wParam, lParam);
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

void MainWindow::OnSize(int width, int height) 
{
   splitWindow->Move(0, 0, width, height);
}

