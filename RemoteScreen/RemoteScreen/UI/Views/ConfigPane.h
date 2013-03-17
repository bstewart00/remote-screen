#pragma once
#ifndef ConfigPane_H
#define ConfigPane_H

#include "Win32Framework/CustomWindow.h"
#include "Win32Framework/CustomWindowBuilder.h"
#include "Win32Framework/ListBox.h"
#include <memory>
#include <Windows.h>
#include <vector>

class ConfigPane : public CustomWindow
{
   friend class CustomWindowBuilder<ConfigPane>;
public:
   static std::unique_ptr<ConfigPane> Create(HINSTANCE hInstance, const CustomWindow& parent);

   LRESULT CALLBACK ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);

private:
   ConfigPane() : CustomWindow() {}

   void OnCreate();
   LRESULT OnCommand(WPARAM wParam, LPARAM lParam);
   void OnResize() const;
   void OnMonitorListSelectionChanged() const;

   static BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);
   void AddTreeViewItems();
   std::unique_ptr<ListBox> monitorList;
   std::vector<HMONITOR> monitors;

   static const int monitorListId = 1;
};

#endif