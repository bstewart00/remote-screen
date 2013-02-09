#include "ContentPane.h"
#include "../WindowHandle.h"
#include "../WindowFactory.h"
#include "../WindowController.h"
#include "../../../resource.h"
#include "../../../Utils/StringResource.h"
#include "../../Controls/TreeView/TreeView.h"

std::unique_ptr<ContentPane> ContentPane::Create(const WindowHandle& parent, HINSTANCE hInstance)
{
   WindowFactory wndFactory(hInstance);
   WindowHandle root = wndFactory.CreateDefaultChild(parent, StringResource(hInstance, IDC_CONTENTPANE));
   return std::unique_ptr<ContentPane>(new ContentPane(root));
}

ContentPane::ContentPane(HWND hwnd)
   : WindowHandle(hwnd)
{

}
