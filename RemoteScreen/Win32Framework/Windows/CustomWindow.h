#pragma once
#ifndef CustomWindow_H
#define CustomWindow_H

#include "CustomWindowBuilder.h"
#include "../WindowHandle.h"
#include "../Utils/StringConverter.h"
#include "../WindowsException.h"
#include <Windows.h>

class CustomWindow : public WindowHandle
{
   friend class CustomWindowBuilder<CustomWindow>;
public:
   virtual ~CustomWindow() {}

   virtual LRESULT CALLBACK ProcessMessage(UINT msg, WPARAM wParam, LPARAM lParam)
   {
      return ::DefWindowProc(hWnd, msg, wParam, lParam);
   }

protected:
   CustomWindow() : WindowHandle() {}
};

#endif