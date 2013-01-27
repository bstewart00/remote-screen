#include "ContentPane.h"
#include "../Window.h"
#include "../WindowClass.h"
#include "../WindowFactory.h"
#include "../WindowController.h"
#include "../../../resource.h"
#include "../../../StringResource.h"
#include "../../Controls/TreeView/TreeView.h"

std::unique_ptr<ContentPane> ContentPane::Create(const Window& parent, HINSTANCE hInstance)
{
   Window root = WindowFactory::CreateDefaultChild(parent, StringResource(hInstance, IDC_CONTENTPANE), hInstance);
   return std::unique_ptr<ContentPane>(new ContentPane(root));
}

ContentPane::ContentPane(HWND hwnd)
   : Window(hwnd)
{

}
