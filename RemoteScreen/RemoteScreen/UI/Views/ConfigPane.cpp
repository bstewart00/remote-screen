#include "../../stdafx.h"
#include "ConfigPane.h"
#include "../../Utils/StringResource.h"
#include "../../resource.h"
#include <boost/format.hpp>

std::unique_ptr<ConfigPane> ConfigPane::Create(HINSTANCE hInstance, const Window& parent)
{
   return WindowBuilder<ConfigPane>(hInstance)
      .ClassName(StringResource(IDC_CONFIGPANE))
      .Style(WS_CHILD | WS_VISIBLE)
      .Parent(parent)
      .Position(0, 0, 200, 100)
      .Register()
      .Create();
}

LRESULT CALLBACK ConfigPane::ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
   switch (message) {
   case WM_CREATE:
      OnCreate();
      break;
   }

   return Window::ProcessMessage(message, wParam, lParam);
}

void ConfigPane::OnCreate()
{
   child = WindowBuilder<Window>(GetInstance())
      .ClassName("STATIC")
      .Style(WS_CHILD | WS_VISIBLE)
      .Parent(*this)
      .Title("Some Button")
      .Position(20, 20, 50, 50)
      .Create2();

   treeview = TreeView::Create(GetInstance(), *this);
   AddTreeViewItems();
}

void ConfigPane::AddTreeViewItems()
{
   treeview->AddItem("Monitor");

   for (int deviceId = 0;;deviceId++) {
      DISPLAY_DEVICE device;
      device.cb = sizeof(DISPLAY_DEVICE);

      BOOL result = ::EnumDisplayDevices(NULL, deviceId, &device, 0);
      if (result == 0) break;

      if (device.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP) {
         DISPLAY_DEVICE named_device;
         named_device.cb = sizeof(DISPLAY_DEVICE);

         result = ::EnumDisplayDevices(device.DeviceName, 0, &named_device, 0);
         if (result != 0) {
            display_devices.push_back(named_device);
            std::string text = boost::str(boost::format("Monitor %1% - %2%") % (deviceId + 1) % StringConverter::ToUtf8(named_device.DeviceString));
            treeview->AddItem(text);
         }
      }
   }
}

//
//void ConfigPane::Move(int x, int y, int width, int height) const
//{
//   Window::Move(x, y, width, height);
//   treeview.Move(x, y, width, height);
//}