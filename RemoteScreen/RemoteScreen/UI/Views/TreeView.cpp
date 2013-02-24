#include "../../stdafx.h"
#include "TreeView.h"
#include "../../Utils/StringConverter.h"
#include "../../WindowsException.h"

#include <CommCtrl.h>

bool TreeView::initialized = false;
void TreeView::Initialize()
{
   INITCOMMONCONTROLSEX params;
   params.dwSize = sizeof(INITCOMMONCONTROLSEX);
   params.dwICC = ICC_TREEVIEW_CLASSES;
   bool initialized = ::InitCommonControlsEx(&params) != 0;
   if (!initialized)
      throw WindowsException("Failed to initialize tree view classes");
   TreeView::initialized = true;
}

std::unique_ptr<TreeView> TreeView::Create(HINSTANCE hInstance, const Window<>& parent)
{
   if (!TreeView::initialized)
      TreeView::Initialize();

   RECT parentClientRect = parent.GetClientRect();
   return SystemWindowBuilder<TreeView>(hInstance)
      .ClassName(WC_TREEVIEW)
      .Style(WS_CHILD | WS_VISIBLE | TVS_HASLINES)
      .Parent(parent)
      .Position(100, 300, 200, 200)
      .Create();
}

void TreeView::AddItem(std::string item)
{
   TVITEM tvi; 
   TVINSERTSTRUCT tvins; 

   tvi.mask = TVIF_TEXT; 
   tvi.cChildren = 0;

   std::wstring text = StringConverter::ToWide(item);

   tvi.pszText = const_cast<wchar_t*>(text.c_str());
   tvi.cchTextMax = text.length();

   tvins.item = tvi; 
   tvins.hParent = NULL; 
   tvins.hInsertAfter = TVI_ROOT;

   HTREEITEM hti = TreeView_InsertItem(hWnd, &tvins);
   if (hti == NULL) {
      throw WindowsException("TreeView insert item failed");
   }
}