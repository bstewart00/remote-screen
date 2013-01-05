#pragma once
#ifndef WINDOWCONTROLLER_H
#define WINDOWCONTROLLER_H

#include "Window.h"
#include <Windows.h>

class WindowController
{
public:
   WindowController(Window window);

   template<class Controller>
   static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
   {
      Controller* controller = nullptr;

      if (message == WM_NCCREATE) {
         Window window(hwnd);
         controller = new Controller(window);
         window.SetLongPtr(controller, GWLP_USERDATA);
      } else {
         controller = Window::GetLongPtr<Controller*>(hwnd, GWLP_USERDATA);
      }

      LRESULT result =  controller
         ? controller->ProcessMessage(message, wParam, lParam)
         : ::DefWindowProc(hwnd, message, wParam, lParam);

      if (message == WM_DESTROY) {
         Window::SetLongPtr(hwnd, nullptr, GWLP_USERDATA);
         delete controller;
      }

      return result;
   }

   static LRESULT CALLBACK DefaultWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
   {
      return ::DefWindowProc(hwnd, message, wParam, lParam);
   }

protected:
   virtual LRESULT ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);
   Window window;
};

#endif