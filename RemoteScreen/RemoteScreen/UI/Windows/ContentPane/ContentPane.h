#pragma once
#ifndef CONTENTPANE_H
#define CONTENTPANE_H

#include <Windows.h>
#include "../Window.h"

class ContentPane
{
public:
   ContentPane(const Window& parent, HINSTANCE hInstance);
   ~ContentPane();

   operator const Window&() const { return rootWindow; }

private:
   Window CreateRootWindow(const Window& parent, HINSTANCE hInstance);

   Window rootWindow;
};

#endif