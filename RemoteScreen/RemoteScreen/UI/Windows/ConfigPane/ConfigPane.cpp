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
   WindowClass paneWndClass(WindowController::DefaultWndProc, StringResource(hInstance, IDC_CONFIGPANE), hInstance);
   paneWndClass.Register();

   WindowFactory paneWndFactory(paneWndClass);
   paneWndFactory.AddStyle(WS_CHILD | WS_VISIBLE);
   paneWndFactory.SetParent(parent);
   return paneWndFactory.Create(hInstance);
}

void ConfigPane::AddTreeViewItems()
{
}