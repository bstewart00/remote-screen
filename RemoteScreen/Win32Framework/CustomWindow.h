#pragma once
#ifndef CustomWindow_H
#define CustomWindow_H

#include "CustomWindowBuilder.h"
#include "WindowHandle.h"
#include <Windows.h>
#include <string>
#include <functional>
#include <cassert>
#include "Utils/StringConverter.h"
#include "WindowsException.h"
#include <memory>

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