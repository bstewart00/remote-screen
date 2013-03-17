#include "ListBox.h"
#include "../Utils/StringConverter.h"
#include "../WindowsException.h"
#include <CommCtrl.h>

namespace Win32
{
   bool ListBox::initialized = false;
   void ListBox::Initialize()
   {
      INITCOMMONCONTROLSEX params;
      params.dwSize = sizeof(INITCOMMONCONTROLSEX);
      params.dwICC = ICC_STANDARD_CLASSES;
      bool initialized = ::InitCommonControlsEx(&params) != 0;
      if (!initialized)
         throw WindowsException("Failed to initialize tree view classes");
      ListBox::initialized = true;
   }

   std::unique_ptr<ListBox> ListBox::Create(HINSTANCE hInstance, const WindowHandle& parent)
   {
      if (!initialized)
         Initialize();

      RECT parentClientRect = parent.GetClientRect();
      return CommonControlBuilder<ListBox>(hInstance)
         .ClassName(WC_LISTBOX)
         .Style(WS_CHILD | WS_VISIBLE)
         .Parent(parent)
         .Create();
   }

   void ListBox::AddItem(std::string item, LPARAM data)
   {
      std::wstring text = StringConverter::ToWide(item);
      LRESULT insertedIndex = SendMsg(LB_ADDSTRING, NULL, reinterpret_cast<LPARAM>(text.c_str()));
      if (insertedIndex == LB_ERR || insertedIndex == LB_ERRSPACE) {
         throw WindowsException("ListBox insert item failed");
      }

      if (SendMsg(LB_SETITEMDATA, insertedIndex, data) == LB_ERR) {
         //TODO: Error
      }
   }
}