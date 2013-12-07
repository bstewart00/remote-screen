#include "stdafx.h"
#include "ConfigPane.h"
#include "Win32Framework/Utils/StringResource.h"
#include "../../resource.h"
#include "Win32Framework/Controls/CommonControlBuilder.h"
#include <boost/format.hpp>
#include <CommCtrl.h>
#include <iostream>
#include <array>

std::unique_ptr<ConfigPane> ConfigPane::Create(HINSTANCE hInstance, const Window& parent)
{
   return Win32::WindowBuilder<ConfigPane>(hInstance)
      .ClassName(Win32::StringResource(IDC_CONFIGPANE))
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
   case WM_COMMAND:
      return OnCommand(wParam, lParam);
   }

   return Window::ProcessMessage(message, wParam, lParam);
}

void ConfigPane::OnCreate()
{
   HINSTANCE hInstance = GetInstance();

   monitorList = Win32::CommonControlBuilder<Win32::ListBox>(hInstance)
      .ClassName(WC_LISTBOX)
      .Id(monitorListId)
      .Parent(*this)
      .Style(WS_CHILD | WS_VISIBLE | LBS_STANDARD)
      .Create();

   AddTreeViewItems();
}

LRESULT ConfigPane::OnCommand(WPARAM wParam, LPARAM lParam)
{
   int controlId = LOWORD(wParam);
   int notificationCode = HIWORD(wParam);

   switch (notificationCode) {
   case LBN_SELCHANGE:
      if (controlId == monitorListId)
         OnMonitorSelected();
      break;
   }
   return 0;
}

void ConfigPane::OnMonitorSelected() const
{
   LRESULT selectedItemIndex = monitorList->SendMsg(LB_GETCURSEL);
   if (selectedItemIndex != LB_ERR) {

      std::array<wchar_t, 255> buf;
      LRESULT selectedItem = monitorList->SendMsg(LB_GETTEXT, selectedItemIndex, reinterpret_cast<LPARAM>(buf.data()));
      if (selectedItem != LB_ERR) {
         NotifyListeners(&ConfigPaneListener::OnMonitorSelected);
      }
   }
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

      std::string text = boost::str(boost::format("Monitor %1%") % Common::StringConverter::ToUtf8(info.szDevice));
      monitorList->AddItem(text);
   }
}

void ConfigPane::OnResize() const
{
   RECT rect = GetClientRect();
   monitorList->Move(rect.left, rect.top, rect.right, rect.bottom);
}