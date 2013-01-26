#include "ConfigPane.h"
#include "../../Controls/TreeView/TreeView.h"
#include "../WindowClass.h"
#include "../WindowController.h"
#include "../WindowFactory.h"
#include "../../../Resource.h"

ConfigPane::ConfigPane(const Window& parent, HINSTANCE hInstance)
   : rootWindow(CreateRootWindow(parent, hInstance)), 
   treeview(TreeView::Create(rootWindow, hInstance))
{
   AddTreeViewItems();
}


ConfigPane::~ConfigPane()
{
}

Window ConfigPane::CreateRootWindow(const Window& parent, HINSTANCE hInstance)
{
   return WindowFactory::CreateDefaultChild(parent, StringResource(hInstance, IDC_CONFIGPANE), hInstance);
}

void ConfigPane::AddTreeViewItems()
{
}