#include "stdafx.h"
#include "MainWindow.h"
#include "Win32Framework/CustomWindowBuilder.h"
#include "Win32Framework/Utils/StringResource.h"
#include "Win32Framework/SplitWindow.h"
#include "../../Resource.h"
#include <algorithm>
#include <iostream>
#include <functional>
#include "ConfigPane.h"
#include "ContentPane.h"

std::unique_ptr<MainWindow> MainWindow::Create(HINSTANCE hInstance)
{
   return CustomWindowBuilder<MainWindow>(hInstance)
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

   return CustomWindow::ProcessMessage(message, wParam, lParam);
}

void MainWindow::OnCreate()
{
   HINSTANCE hInstance = GetInstance();

   std::unique_ptr<ConfigPane> configPane = ConfigPane::Create(hInstance, *this);
   std::unique_ptr<ContentPane> contentPane = ContentPane::Create(hInstance, *this);

   splitWindow = SplitWindow::Create(hInstance, *this, std::move(configPane), std::move(contentPane), splitterPercentage);
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
   case IDC_CONFIGPANE:
      std::cout << "IDC_CONFIGPANE" << wParam << lParam << std::endl;
      return 0;
      break;
   case WM_SIZE:
      OnSize(LOWORD(lParam), HIWORD(lParam));
      return 0;
   }

   return CustomWindow::ProcessMessage(WM_COMMAND, wParam, lParam);
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

