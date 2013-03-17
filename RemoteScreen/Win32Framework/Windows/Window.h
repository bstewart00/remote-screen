#pragma once
#ifndef Window_H
#define Window_H

#include "WindowBuilder.h"
#include "../WindowHandle.h"
#include "../Utils/StringConverter.h"
#include "../WindowsException.h"
#include <Windows.h>

namespace Win32
{
   class Window : public WindowHandle
   {
      friend class WindowBuilder<Window>;
   public:
      virtual ~Window() {}

      virtual LRESULT CALLBACK ProcessMessage(UINT msg, WPARAM wParam, LPARAM lParam)
      {
         return ::DefWindowProc(hWnd, msg, wParam, lParam);
      }

   protected:
      Window() : WindowHandle() {}
   };
}

#endif