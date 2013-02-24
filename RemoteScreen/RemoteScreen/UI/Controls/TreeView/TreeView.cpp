//#include "../../../stdafx.h"
//#include "TreeView.h"
//#include "../../Windows/WindowBuilder.h"
//#include "../../../Utils/StringConverter.h"
//#include "../../../WindowsException.h"
//
//#include <CommCtrl.h>
//
//bool TreeView::initialized = false;
//void TreeView::Initialize()
//{
//   INITCOMMONCONTROLSEX params;
//   params.dwSize = sizeof(INITCOMMONCONTROLSEX);
//   params.dwICC |= ICC_TREEVIEW_CLASSES;
//   ::InitCommonControlsEx(&params);
//}
//
//TreeView TreeView::Create(const Window& parent, HINSTANCE hInstance)
//{
//   if (!TreeView::initialized)
//      TreeView::Initialize();
//
//   RECT parentClientRect = parent.GetClientRect();
//   WindowBuilder<Window> wndFactory(hInstance);
//   std::unique_ptr<Window> window = wndFactory.Create(StringConverter::ToUtf8(WC_TREEVIEW), WS_VISIBLE | WS_CHILD | TVS_HASLINES, parent, "", 0, 0, parentClientRect.right, parentClientRect.bottom);
//   window->Show();
//   return TreeView(*window);
//}
//
//void TreeView::AddItem(std::string item)
//{
//   TVITEM tvi; 
//   TVINSERTSTRUCT tvins; 
//
//   tvi.mask = TVIF_TEXT; 
//
//   std::wstring* text = StringConverter::ToWide(item).get();
//
//   tvi.pszText = const_cast<wchar_t*>(text->c_str());
//   tvi.cchTextMax = text->length();
//
//   tvins.item = tvi; 
//   tvins.hInsertAfter = TVI_SORT; 
//   tvins.hParent = TVI_ROOT; 
//
//   HTREEITEM hti = TreeView_InsertItem(hWnd, &tvins);
//   if (hti == NULL) {
//      throw WindowsException("TreeView insert item failed");
//   }
//}
//
//TreeView::TreeView(HWND hwnd)
//   : Window(hwnd)
//{
//}