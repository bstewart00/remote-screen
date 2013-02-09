#pragma once
#ifndef MainWindowView_H
#define MainWindowView_H

#include "../Windows/Window.h"
#include <Windows.h>

class MainWindowView
{
public:
   MainWindowView(HINSTANCE hInstance);

   void Display(int nCmdShow);

private:
   Window MakeWindow();

   Window window;
   HINSTANCE hInstance;
};

#endif