#pragma once
#ifndef WINDOWCLASS_H
#define WINDOWCLASS_H

#include "../WindowsException.h"
#include <Windows.h>

class WindowClass
{
public:
   WindowClass(WNDPROC wndProc, std::string name, HINSTANCE hInst);
   void Register();
   HWND GetRunningWindow ();
   std::string GetName() const { return name; }
   HINSTANCE GetInstance() const { return hInstance; }

protected:
   std::string name;
   WNDCLASSEX wndClass;
   HINSTANCE hInstance;
};

#endif