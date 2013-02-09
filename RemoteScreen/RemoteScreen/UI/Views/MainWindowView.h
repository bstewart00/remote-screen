#pragma once
#ifndef MainWindowView_H
#define MainWindowView_H

#include "../Windows/WindowHandle.h"
#include <Windows.h>

class MainWindowView
{
public:
   MainWindowView(HINSTANCE hInstance);

   void Display(int nCmdShow);

private:
   WindowHandle MakeWindow();

   WindowHandle window;
   HINSTANCE hInstance;
};

#endif