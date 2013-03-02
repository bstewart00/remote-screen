#pragma once
#ifndef ConfigPane_H
#define ConfigPane_H

#include "Win32Framework/Window.h"
#include "Win32Framework/WindowBuilder.h"
#include "Win32Framework/TreeView.h"
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

   static BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);
   void AddTreeViewItems();
   std::unique_ptr<TreeView> treeview;
   std::vector<HMONITOR> monitors;
};

#endif