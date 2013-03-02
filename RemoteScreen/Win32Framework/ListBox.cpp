#include "ListBox.h"
#include "Utils/StringConverter.h"
#include "WindowsException.h"

#include <CommCtrl.h>

std::unique_ptr<ListBox> ListBox::Create(HINSTANCE hInstance, const Window<>& parent)
{
   RECT parentClientRect = parent.GetClientRect();
   return SystemWindowBuilder<ListBox>(hInstance)
      .ClassName(WC_LISTBOX)
      .Style(WS_CHILD | WS_VISIBLE)
      .Parent(parent)
      .Create();
}

void ListBox::AddItem(std::string item)
{
   std::wstring text = StringConverter::ToWide(item);
   LRESULT result = SendMessageW(LB_ADDSTRING, NULL, reinterpret_cast<LPARAM>(text.c_str()));
   if (result == LB_ERR || result == LB_ERRSPACE) {
      throw WindowsException("ListBox insert item failed");
   }
}