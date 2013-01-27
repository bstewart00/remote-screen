#include "TreeView.h"
#include "../../Windows/WindowFactory.h"
#include "../../../StringConverter.h"
#include "../../../WindowsException.h"

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
   wndFactory.SetPosition(0, 0, 100, 200);//parentClientRect.right, parentClientRect.bottom);
   wndFactory.SetParent(parent);
   wndFactory.AddStyle(WS_VISIBLE | WS_CHILD | TVS_HASLINES);

   Window window = wndFactory.Create();
   window.Show();
   return TreeView(window);
}

void TreeView::AddItem(std::string item)
{
   TVITEM tvi; 
   TVINSERTSTRUCT tvins; 

   tvi.mask = TVIF_TEXT; 

   std::wstring* text = StringConverter::ToWide(item).get();

   tvi.pszText = const_cast<wchar_t*>(text->c_str());
   tvi.cchTextMax = text->length();

   tvins.item = tvi; 
   tvins.hInsertAfter = TVI_FIRST; 
   tvins.hParent = TVI_ROOT; 

   HTREEITEM hti = TreeView_InsertItem(hWnd, &tvins);
   if (hti == NULL) {
      throw WindowsException("TreeView insert item failed");
   }

   TVITEM testItem;
   wchar_t buf[255];
   testItem.pszText = buf;
   testItem.cchTextMax = 255;
   testItem.mask = TVIF_TEXT;
   BOOL result = TreeView_GetItem(hWnd, &testItem);
}

TreeView::TreeView(HWND hwnd)
   : Window(hwnd)
{
}