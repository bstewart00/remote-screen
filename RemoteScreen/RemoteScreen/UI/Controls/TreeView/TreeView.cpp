#include "TreeView.h"
#include "../../Windows/WindowFactory.h"

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

TreeView TreeView::Create(const Window& parent, HINSTANCE hInstance)
{
   if (!TreeView::initialized)
      TreeView::Initialize();

   RECT parentClientRect = parent.GetClientRect();
   WindowClass wndClass(boost::nowide::narrow(WC_TREEVIEW), hInstance);
   WindowFactory wndFactory(wndClass);
   wndFactory.SetPosition(0, 0, parentClientRect.right, parentClientRect.bottom);
   wndFactory.SetParent(parent);
   wndFactory.AddStyle(WS_VISIBLE | WS_CHILD | TVS_HASLINES);

   Window window = wndFactory.Create();
   window.Show();
   return TreeView(window);
}

void TreeView::AddItem(std::string item)
{
    //TVITEM tvi; 
    //TVINSERTSTRUCT tvins; 
    //HTREEITEM hti; 

    //tvi.mask = TVIF_TEXT; 

    //boost::nowide::widen(

    //auto test = const_cast<wchar_t*>(boost::nowide::widen(item).c_str());
    //tvi.pszText = test;
    //tvi.cchTextMax = 5; 

    //tvins.item = tvi; 
    //tvins.hInsertAfter = TVI_FIRST; 
    //tvins.hParent = TVI_ROOT; 

    //(HTREEITEM)SendMessage(TVM_INSERTITEM, 0, (LPARAM)(LPTVINSERTSTRUCT)&tvins); 
}

TreeView::TreeView(HWND hwnd)
   : Window(hwnd)
{
}

TreeView::~TreeView()
{
}
