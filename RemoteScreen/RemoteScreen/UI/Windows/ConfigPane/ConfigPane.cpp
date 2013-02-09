#include "ConfigPane.h"
#include "../../Controls/TreeView/TreeView.h"
#include "../WindowFactory.h"
#include "ConfigPaneController.h"
#include "../../../Resource.h"
#include "../../../Utils/StringResource.h"
#include "../../../Utils/StringConverter.h"
#include <boost/format.hpp>

std::unique_ptr<ConfigPane> ConfigPane::Create(const Window& parent, HINSTANCE hInstance)
{   
   StringResource className = StringResource(IDC_CONFIGPANE);

   WindowFactory factory(hInstance);
   factory.SetClassName(className);
   factory.SetWndProc(WindowController::WndProc<ConfigPaneController>);

   Window root = factory.Create(className, WS_CHILD | WS_VISIBLE, parent);
   TreeView treeview = TreeView::Create(root, hInstance);

   return std::unique_ptr<ConfigPane>(new ConfigPane(root, treeview));
}

ConfigPane::ConfigPane(HWND hwnd, TreeView treeview)
   : Window(hwnd), treeview(treeview)
{
   //AddTreeViewItems();
}

void ConfigPane::AddTreeViewItems()
{
   treeview.AddItem("Monitor");

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
            treeview.AddItem(text);
         }
      }
   }
}

void ConfigPane::Move(int x, int y, int width, int height) const
{
   Window::Move(x, y, width, height);
   treeview.Move(x, y, width, height);
}