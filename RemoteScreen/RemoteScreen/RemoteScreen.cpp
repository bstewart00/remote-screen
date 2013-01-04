// RemoteScreen.cpp : Defines the entry point for the application.
//

#include "resource.h"
#include "UI/Windows/Main/MainWindow.h"
#include "UI/Windows/Main/MainWindowClass.h"
#include "UI/Windows/Main/MainWindowController.h"
#include "StringResource.h"
#include "WindowsException.h"

#include <Windows.h>
#include <sstream>
#include <array>
#include <string>
#include <boost/format.hpp>
#include <boost/nowide/convert.hpp>

void OutOfMemoryHandler()
{
   throw WindowsException("Out of memory");
}

bool RestoreExistingWindow(WindowClass& windowClass)
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

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
   std::set_new_handler(OutOfMemoryHandler);

   try {

      StringResource mainWndClassName(hInstance, IDC_REMOTESCREEN);
      StringResource mainWindowTitle(hInstance, IDS_APP_TITLE);

      MainWindowClass mainWndClass(WindowController::WndProc<MainWindowController>, mainWndClassName, hInstance, IDI_REMOTESCREEN, IDI_SMALL, IDC_REMOTESCREEN);
      if (RestoreExistingWindow(mainWndClass))
         return 0;
      mainWndClass.Register();

      MainWindow mainWindow(mainWndClass, mainWindowTitle);
      mainWindow.Create();
      mainWindow.Show(nCmdShow);

      HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_REMOTESCREEN));
      MSG msg;
      BOOL bRet;
      while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0) {
         if (bRet == -1) {
            return -1;
         } else if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
         }
      }

      return (int) msg.wParam;
   } catch (WindowsException e) {
      boost::format test = boost::format("Error: %1 Win32 Error %2: %3") % e.GetMessage() % e.GetErrorCode() % e.GetFormattedMessage();
      std::wstring message(boost::nowide::widen(test.str()));
      ::MessageBox (0, message.c_str(), L"Exception", MB_ICONEXCLAMATION | MB_OK);
   } catch (...) {
      ::MessageBox (0, L"Unknown Error", L"Exception", MB_ICONEXCLAMATION | MB_OK);
   }

   return 0;
}
