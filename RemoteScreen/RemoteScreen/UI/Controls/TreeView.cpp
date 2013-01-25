#include "TreeView.h"
#include "../Windows/WindowFactory.h"

#include <Windows.h>
#include <CommCtrl.h>

bool TreeView::initialized = false;
void TreeView::Initialize()
{
   INITCOMMONCONTROLSEX params;
   params.dwSize = sizeof(INITCOMMONCONTROLSEX);
   params.dwICC |= ICC_TREEVIEW_CLASSES;
   ::InitCommonControlsEx(&params);
}

TreeView::TreeView(const Window& parent, HINSTANCE hInstance)
   : parent(parent), treeview(nullptr), hInstance(hInstance)
{
   if (!TreeView::initialized)
      TreeView::Initialize();

   RECT parentClientRect = parent.GetClientRect();

   WindowClass wndClass(boost::nowide::narrow(WC_TREEVIEW), hInstance);
   ChildWindowFactory wndFactory(wndClass, parent);

   wndFactory.SetPosition(0, 0, parentClientRect.right, parentClientRect.bottom);
   wndFactory.AddStyle(WS_BORDER | TVS_HASLINES);

   treeview = wndFactory.Create();
}

TreeView::~TreeView()
{
}
