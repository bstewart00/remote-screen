#pragma once
#ifndef CONFIGPANE_H
#define CONFIGPANE_H

#include "../Window.h"
#include "../../Controls/TreeView/TreeView.h"
#include <Windows.h>

class ConfigPane
{
public:
   ConfigPane(const Window& parent, HINSTANCE hInstance);
   ~ConfigPane();
   
   operator const Window&() const { return rootWindow; }
private:
   Window CreateRootWindow(const Window& parent, HINSTANCE hInstance);
   void AddTreeViewItems();

   Window rootWindow;
   TreeView treeview;
};

#endif