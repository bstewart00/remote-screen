#include "../../stdafx.h"
#include "MainWindow.h"
#include "ContentPane.h"
#include "Splitter.h"
#include "../Windows/WindowFactory.h"
#include "../../CustomMessages.h"
#include "../../Utils/StringResource.h"
#include "../../Resource.h"
#include "ConfigPane.h"
#include <algorithm>
#include <functional>

std::unique_ptr<MainWindow> MainWindow::Create(HINSTANCE hInstance)
{
   WindowFactory<MainWindow> factory(hInstance);
   factory.SetStyle(CS_HREDRAW | CS_VREDRAW);
   factory.SetMenu(IDC_REMOTESCREEN);
   factory.SetResIcons(IDI_REMOTESCREEN);
   return factory.Create(StringResource(IDC_REMOTESCREEN), WS_OVERLAPPEDWINDOW, nullptr, StringResource(IDS_APP_TITLE));
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

   leftWin = ConfigPane::Create(hInstance, *this);
   rightWin = ContentPane::Create(hInstance, *this);
   splitter = Splitter::Create(hInstance, *this);
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
   case MSG_MOVESPLITTER:
      MoveSplitter(wParam);
      return 0;
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

void MainWindow::OnSize(int width, int height) 
{
   this->width = width;
   this->height = height;

   int splitterX = CalculateSplitterX();
   int splitterSize = splitter->GetSize();

   splitter->MoveDelayPaint(splitterX, 0, splitterSize, this->height);
   leftWin->Move(0, 0, splitterX, this->height);
   rightWin->Move(splitterX + splitterSize, 0, this->width - splitterX - splitterSize, this->height);
   splitter->ForceRepaint();
}

int MainWindow::CalculateSplitterX()
{
   int splitterX = (width * splitRatioPercentage) / 100;
   if (splitterX < 0)
      splitterX = 0;

   return splitterX;
}

void MainWindow::MoveSplitter (int splitterX)
{
   splitRatioPercentage = CalculateSplitterPercentage(splitterX);
   OnSize(width, height);
}

int MainWindow::CalculateSplitterPercentage(int splitterX)
{
   int newPercent = splitterX * 100 / width;
   if (newPercent < 0)
      newPercent = 0;
   else if (newPercent > 100)
      newPercent = 100;

   return newPercent;
}