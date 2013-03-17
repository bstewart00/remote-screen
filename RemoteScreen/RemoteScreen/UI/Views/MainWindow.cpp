#include "stdafx.h"
#include "MainWindow.h"
#include "Win32Framework/Windows/WindowBuilder.h"
#include "Win32Framework/Utils/StringResource.h"
#include "Win32Framework/Windows/SplitWindow.h"
#include "../../Resource.h"
#include <algorithm>
#include <iostream>
#include <functional>
#include "ConfigPane.h"
#include "ContentPane.h"

std::unique_ptr<MainWindow> MainWindow::Create(HINSTANCE hInstance)
{
   return Win32::WindowBuilder<MainWindow>(hInstance)
      .ClassName(Win32::StringResource(IDC_REMOTESCREEN))
      .ClassStyle(CS_HREDRAW | CS_VREDRAW)
      .ClassMenu(IDC_REMOTESCREEN)
      .Style(WS_OVERLAPPEDWINDOW)
      .Icon(IDI_REMOTESCREEN)
      .Title(Win32::StringResource(IDS_APP_TITLE))
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

   std::unique_ptr<ConfigPane> configPane = ConfigPane::Create(hInstance, *this);
   configPane->AddListener(this);

   std::unique_ptr<ContentPane> contentPane = ContentPane::Create(hInstance, *this);

   splitWindow = Win32::SplitWindow::Create(hInstance, *this, std::move(configPane), std::move(contentPane), splitterPercentage);
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

Win32::ModalDialog MainWindow::CreateAboutDialog()
{
   return Win32::ModalDialog(GetInstance(), IDD_ABOUTBOX, hWnd);
}

ApplicationSettingsDialog MainWindow::CreateApplicationSettingsDialog()
{
   return ApplicationSettingsDialog(GetInstance(), IDD_SETTINGS, hWnd);
}

void MainWindow::OnSize(int width, int height) 
{
   splitWindow->Move(0, 0, width, height);
}

void MainWindow::OnMonitorSelected()
{
   std::cout << "MainWindow: MonitorSelected" << std::endl;
}
