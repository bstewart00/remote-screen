#include "Application.h"
#include "StringResource.h"
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
   StringResource mainWndClassName(hInstance, IDC_REMOTESCREEN);
   StringResource mainWindowTitle(hInstance, IDS_APP_TITLE);

   WindowClass mainWndClass(WindowController::WndProc<MainWindowController>, mainWndClassName, hInstance);
   mainWndClass.SetSizeRedraw();
   mainWndClass.SetMenu(IDC_REMOTESCREEN);
   mainWndClass.SetResIcons(IDI_REMOTESCREEN);

   if (RestoreExistingWindow(mainWndClass))
      return false;
   mainWndClass.Register();

   WindowFactory mainWindowFactory(mainWndClass);
   mainWindowFactory.AddStyle(WS_OVERLAPPEDWINDOW | WS_VISIBLE);
   mainWindowFactory.SetTitle(mainWindowTitle);

   Window mainWindow(mainWindowFactory.Create());
   mainWindow.Show(nCmdShow);

   return true;
}

int Application::Run()
{
   HACCEL hAccelTable = ::LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_REMOTESCREEN));
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

bool Application::RestoreExistingWindow(const WindowClass& windowClass)
{
   HWND hwndOther = windowClass.GetRunningWindow ();
   if (hwndOther != 0) {
      ::SetForegroundWindow (hwndOther);
      if (::IsIconic (hwndOther))
         ::ShowWindow (hwndOther, SW_RESTORE);
      return true;
   }

   return false;
}
