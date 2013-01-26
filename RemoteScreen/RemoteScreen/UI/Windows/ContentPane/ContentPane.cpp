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
   WindowClass paneWndClass(WindowController::DefaultWndProc, StringResource(hInstance, IDC_CONTENTPANE), hInstance);
   paneWndClass.SetSysCursor(IDC_IBEAM);
   paneWndClass.Register();

   WindowFactory paneWndFactory(paneWndClass);
   paneWndFactory.AddStyle(WS_CHILD | WS_VISIBLE);
   paneWndFactory.SetParent(parent);

   return paneWndFactory.Create();
}