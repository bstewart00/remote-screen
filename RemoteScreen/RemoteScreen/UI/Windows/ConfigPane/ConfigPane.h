#pragma once
#ifndef CONFIGPANE_H
#define CONFIGPANE_H

#include "../WindowHandle.h"
#include "../../Controls/TreeView/TreeView.h"
#include <memory>
#include <vector>

class ConfigPane : public WindowHandle
{
public:
   static std::unique_ptr<ConfigPane> Create(const WindowHandle& parent, HINSTANCE hInstance);
   void Move(int x, int y, int width, int height) const;

private:
   ConfigPane(HWND hwnd, TreeView treeview);
   void AddTreeViewItems();
   TreeView treeview;
   std::vector<DISPLAY_DEVICE> display_devices;
};

#endif