#pragma once
#ifndef ConfigPane_H
#define ConfigPane_H

#include "Win32Framework/Windows/Window.h"
#include "Win32Framework/Windows/WindowBuilder.h"
#include "Win32Framework/Controls/ListBox.h"
#include <memory>
#include <Windows.h>
#include <vector>

class ConfigPane : public Win32::Window
{
   friend class Win32::WindowBuilder<ConfigPane>;
public:
   static std::unique_ptr<ConfigPane> Create(HINSTANCE hInstance, const Window& parent);

   LRESULT CALLBACK ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);

private:
   ConfigPane() : Window() {}

   void OnCreate();
   LRESULT OnCommand(WPARAM wParam, LPARAM lParam);
   void OnResize() const;
   void OnMonitorListSelectionChanged() const;

   static BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);
   void AddTreeViewItems();
   std::unique_ptr<Win32::ListBox> monitorList;
   std::vector<HMONITOR> monitors;

   static const int monitorListId = 1;
};

#endif