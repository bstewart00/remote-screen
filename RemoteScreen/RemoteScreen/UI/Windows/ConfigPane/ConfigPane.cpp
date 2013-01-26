#include "ConfigPane.h"
#include "../../Controls/TreeView/TreeView.h"

ConfigPane::ConfigPane(const Window& parent, HINSTANCE hInstance)
   : rootWindow(CreateRootWindow(parent, hInstance))
{
}


ConfigPane::~ConfigPane()
{
}

Window ConfigPane::CreateRootWindow(const Window& parent, HINSTANCE hInstance)
{
   TreeView treeview = TreeView::Create(parent, hInstance);
   treeview.AddItem("Monitors");

   return static_cast<Window>(treeview);
}