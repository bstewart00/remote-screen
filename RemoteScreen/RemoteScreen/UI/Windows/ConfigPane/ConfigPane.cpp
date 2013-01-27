#include "ConfigPane.h"
#include "../../Controls/TreeView/TreeView.h"
#include "../WindowClass.h"
#include "../WindowController.h"
#include "../WindowFactory.h"
#include "../../../Resource.h"

std::unique_ptr<ConfigPane> ConfigPane::Create(const Window& parent, HINSTANCE hInstance)
{   
   Window root = WindowFactory::CreateDefaultChild(parent, StringResource(hInstance, IDC_CONFIGPANE), hInstance);
   TreeView treeview(TreeView::Create(root, hInstance));

   return std::unique_ptr<ConfigPane>(new ConfigPane(root, treeview));
}

ConfigPane::ConfigPane(HWND hwnd, TreeView treeview)
   : Window(hwnd), treeview(treeview)
{
   AddTreeViewItems();
}

void ConfigPane::AddTreeViewItems()
{
   treeview.AddItem("Monitor");
   treeview.AddItem("Test");
}

void ConfigPane::Move(int x, int y, int width, int height) const
{
   Window::Move(x, y, width, height);
   treeview.Move(x, y, width, height);
}