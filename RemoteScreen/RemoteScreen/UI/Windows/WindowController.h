#pragma once
#ifndef WINDOWCONTROLLER_H
#define WINDOWCONTROLLER_H

#include "WindowHandle.h"

class WindowController
{
public:
   WindowController(WindowHandle window, CREATESTRUCT* createStruct);

   template<class Controller>
   static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
   {
      Controller* controller = nullptr;

      if (message == WM_NCCREATE) {
         WindowHandle window(hwnd);
         controller = new Controller(window, reinterpret_cast<CREATESTRUCT *>(lParam));
         window.SetLongPtr(controller, GWLP_USERDATA);
      } else {
         controller = WindowHandle::GetLongPtr<Controller*>(hwnd, GWLP_USERDATA);
      }

      LRESULT result =  controller
         ? controller->ProcessMessage(message, wParam, lParam)
         : ::DefWindowProc(hwnd, message, wParam, lParam);

      if (message == WM_DESTROY) {
         WindowHandle::SetLongPtr(hwnd, nullptr, GWLP_USERDATA);
         delete controller;
      }

      return result;
   }

   static LRESULT CALLBACK DefaultWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
   {
      return ::DefWindowProc(hwnd, message, wParam, lParam);
   }

   virtual LRESULT ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam) = 0;
protected:
   WindowHandle window;
};

#endif