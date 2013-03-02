#include "stdafx.h"
#include "ConfigPane.h"
#include "../Win32Framework/Utils/StringResource.h"
#include "../../resource.h"
#include "Win32Framework/SystemWindowBuilder.h"
#include <boost/format.hpp>
#include <CommCtrl.h>

std::unique_ptr<ConfigPane> ConfigPane::Create(HINSTANCE hInstance, const Window& parent)
{
   return WindowBuilder<ConfigPane>(hInstance)
      .ClassName(StringResource(IDC_CONFIGPANE))
      .Style(WS_CHILD | WS_VISIBLE)
      .Parent(parent)
      .Register()
      .Create();
}

LRESULT CALLBACK ConfigPane::ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
   switch (message) {
   case WM_CREATE:
      OnCreate();
      break;
   case WM_SIZE:
      OnResize();
      break;
   }

   return Window::ProcessMessage(message, wParam, lParam);
}

void ConfigPane::OnCreate()
{
   HINSTANCE hInstance = GetInstance();

   monitorList = SystemWindowBuilder<ListBox>(hInstance)
      .ClassName(WC_LISTBOX)
      .Parent(*this)
      .Style(WS_CHILD | WS_VISIBLE)
      .Create();

   AddTreeViewItems();
}

BOOL CALLBACK ConfigPane::MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
{
   ConfigPane* instance = reinterpret_cast<ConfigPane*>(dwData);
   instance->monitors.push_back(hMonitor);

   return TRUE;
}

void ConfigPane::AddTreeViewItems()
{
   ::EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, reinterpret_cast<LPARAM>(this));

   for (auto i = monitors.begin(); i != monitors.end(); ++i) {
      HMONITOR monitor = *i;
      MONITORINFOEX info;
      info.cbSize = sizeof(MONITORINFOEX);
      ::GetMonitorInfoW(monitor, &info);

      std::string text = boost::str(boost::format("Monitor %1%") % StringConverter::ToUtf8(info.szDevice));
      monitorList->AddItem(text);
   }
}

void ConfigPane::OnResize() const
{
   RECT rect = GetClientRect();
   monitorList->Move(rect.left, rect.top, rect.right, rect.bottom);
}