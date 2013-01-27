#include "ContentPane.h"
#include "../Window.h"
#include "../WindowClass.h"
#include "../WindowFactory.h"
#include "../WindowController.h"
#include "../../../resource.h"
#include "../../../StringResource.h"
#include "../../Controls/TreeView/TreeView.h"

ContentPane::ContentPane(const Window& parent, HINSTANCE hInstance)
   : rootWindow(CreateRootWindow(parent, hInstance))
{
   TreeView tv(TreeView::Create(rootWindow, hInstance));
   tv.AddItem("Monitor");
}

ContentPane::~ContentPane()
{
}

Window ContentPane::CreateRootWindow(const Window& parent, HINSTANCE hInstance)
{
   return WindowFactory::CreateDefaultChild(parent, StringResource(hInstance, IDC_CONTENTPANE), hInstance);
}