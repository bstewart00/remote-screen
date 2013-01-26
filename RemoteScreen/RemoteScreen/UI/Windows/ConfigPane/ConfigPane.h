#pragma once
#ifndef CONFIGPANE_H
#define CONFIGPANE_H

#include "../Window.h"
#include <Windows.h>

class ConfigPane
{
public:
   ConfigPane(const Window& parent, HINSTANCE hInstance);
   ~ConfigPane();
   
   operator Window() const { return rootWindow; }
private:
   Window CreateRootWindow(const Window& parent, HINSTANCE hInstance);

   Window rootWindow;
};

#endif