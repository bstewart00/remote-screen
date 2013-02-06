#include "stdafx.h"
#include "Application.h"
#include "Utils/StringResource.h"
#include "UI/Windows/Main/MainWindowController.h"
#include "UI/Windows/WindowFactory.h"
#include "UI/Windows/WindowController.h"
#include "Resource.h"

Application::Application(HINSTANCE hInstance, int nCmdShow)
   : hInstance(hInstance), nCmdShow(nCmdShow)
{
}

bool Application::Initialize()
{
   WindowClass mainWndClass(WindowController::WndProc<MainWindowController>, StringResource(hInstance, IDC_REMOTESCREEN), hInstance);
   mainWndClass.SetSizeRedraw();
   mainWndClass.SetMenu(IDC_REMOTESCREEN);
   mainWndClass.SetResIcons(IDI_REMOTESCREEN);
   mainWndClass.Register();

   WindowFactory mainWindowFactory(mainWndClass);
   mainWindowFactory.AddStyle(WS_OVERLAPPEDWINDOW | WS_VISIBLE);
   mainWindowFactory.SetTitle(StringResource(hInstance, IDS_APP_TITLE));

   Window mainWindow(mainWindowFactory.Create());
   mainWindow.Show(nCmdShow);
   mainWindow.Update();

   return true;
}

int Application::Run()
{
   Initialize();

   HACCEL hAccelTable = LoadAccelerators(StringResource(hInstance, IDC_REMOTESCREEN));
   MSG msg;
   BOOL bRet;
   while ((bRet = ::GetMessage(&msg, NULL, 0, 0)) != 0) {
      if (bRet == -1) {
         return -1;
      } else if (!::TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
         ::TranslateMessage(&msg);
         ::DispatchMessage(&msg);
      }
   }

   return (int) msg.wParam;
}