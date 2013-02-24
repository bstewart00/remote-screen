#pragma once
#ifndef ConfigPane_H
#define ConfigPane_H

#include "../Windows/Window.h"
#include "../Windows/WindowBuilder.h"
#include "TreeView.h"
#include <memory>
#include <Windows.h>
#include <vector>

class ConfigPane : public Window<>
{
   friend class WindowBuilder<ConfigPane>;
public:
   static std::unique_ptr<ConfigPane> Create(HINSTANCE hInstance, const Window& parent);

   LRESULT CALLBACK ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);

private:
   ConfigPane() : Window() {}

   void OnCreate();
   LRESULT OnCommand(WPARAM wParam, LPARAM lParam);
   void OnResize() const;
   
   void AddTreeViewItems();
   std::unique_ptr<TreeView> treeview;
   std::vector<DISPLAY_DEVICE> display_devices;
};

#endif