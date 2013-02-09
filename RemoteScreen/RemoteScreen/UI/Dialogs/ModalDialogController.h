#pragma once
#ifndef MODALDIALOGCONTROLLER_H
#define MODALDIALOGCONTROLLER_H

#include "DialogControllerFactory.h"
#include "../Windows/Window.h"

class ModalDialogController
{
public:
   virtual ~ModalDialogController () {}
   virtual void OnInitDialog (HWND hwnd) = 0;
   virtual bool OnCommand (HWND hwnd, int controllerID, int notifyCode) = 0;
   virtual bool OnNotify (HWND hwnd, int idcontroller, NMHDR *hdr) = 0;

   static INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam)
   {

      ModalDialogController* controller = Window::GetLongPtr<ModalDialogController*> (hwndDlg, GWLP_USERDATA);
      switch (message)
      {
      case WM_INITDIALOG:
         {
            AbstractDialogControllerFactory* factory = reinterpret_cast<AbstractDialogControllerFactory*>(lParam);
            controller = factory->MakeController(hwndDlg);
            Window::SetLongPtr<ModalDialogController*>(hwndDlg, controller, GWLP_USERDATA);
            controller->OnInitDialog (hwndDlg);
         }
         return TRUE;

      case WM_COMMAND:
         if (controller && controller->OnCommand (hwndDlg, LOWORD(wParam), HIWORD (wParam))) {
            return TRUE;
         }
         break;

      case WM_NOTIFY:
         if (controller && controller->OnNotify (hwndDlg, wParam, (NMHDR *)lParam))
            return TRUE;
         break;
      case WM_DESTROY:
         delete controller;
         Window::SetLongPtr<ModalDialogController*> (hwndDlg, 0, GWLP_USERDATA);
         break;
      }
      return FALSE;
   }
};

#endif