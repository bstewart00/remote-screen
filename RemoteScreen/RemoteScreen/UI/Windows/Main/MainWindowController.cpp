#include "MainWindowController.h"
#include "../../../Resource.h"

MainWindowController::MainWindowController(Window* window)
   : WindowController(window)
{
}

INT_PTR CALLBACK MainWindowController::AboutDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
   switch (message) {
   case WM_INITDIALOG:
      return static_cast<INT_PTR>(TRUE);

   case WM_COMMAND:
      if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
         ::EndDialog(hDlg, LOWORD(wParam));
         return  static_cast<INT_PTR>(TRUE);
      }
      break;
   }
   return static_cast<INT_PTR>(FALSE);
}

LRESULT MainWindowController::ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
   int wmId, wmEvent;
   PAINTSTRUCT ps;
   HDC hdc;
   HINSTANCE hInst;

   switch (message) {
   case WM_COMMAND:
      wmId = LOWORD(wParam);
      wmEvent = HIWORD(wParam);
      switch (wmId)
      {
      case IDM_ABOUT:
         hInst = window->GetLongPtr<HINSTANCE>(GWLP_HINSTANCE);
         ::DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), *window, AboutDialogProc);
         break;
      case IDM_EXIT:
         window->Destroy();
         break;
      default:
         return WindowController::ProcessMessage(message, wParam, lParam);
      }
      break;
   case WM_PAINT:
      hdc = ::BeginPaint(*window, &ps);
      TextOut(hdc, 0, 0, L"Test", 4);
      ::EndPaint(*window, &ps);
      break;
   case WM_DESTROY:
      ::PostQuitMessage(0);
      break;
   default:
      return WindowController::ProcessMessage(message, wParam, lParam);
   }

   return 0;
}