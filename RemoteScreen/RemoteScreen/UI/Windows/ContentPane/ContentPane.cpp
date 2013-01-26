#include "ContentPane.h"
#include "../Window.h"
#include "../WindowClass.h"
#include "../WindowFactory.h"
#include "../WindowController.h"
#include "../../../resource.h"
#include "../../../StringResource.h"

ContentPane::ContentPane(const Window& parent, HINSTANCE hInstance)
   : rootWindow(CreateRootWindow(parent, hInstance))
{
}

ContentPane::~ContentPane()
{
}

Window ContentPane::CreateRootWindow(const Window& parent, HINSTANCE hInstance)
{
   return WindowFactory::CreateDefaultChild(parent, StringResource(hInstance, IDC_CONTENTPANE), hInstance);
}