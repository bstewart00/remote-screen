#pragma once
#ifndef ListBox_H
#define ListBox_H

#include "../WindowHandle.h"
#include "CommonControlBuilder.h"
#include <Windows.h>
#include <vector>
#include <string>
#include <memory>

namespace Win32
{
   class ListBox : public WindowHandle
   {
      friend class CommonControlBuilder<ListBox>;
   public:
      static std::unique_ptr<ListBox> Create(HINSTANCE hInstance, const WindowHandle& parent);

      void AddItem(const std::string text, LPARAM data = 0);
   private:
      ListBox(HWND hWnd) : WindowHandle(hWnd) {}

      static bool initialized;
      static void Initialize();
      std::vector<wchar_t*> text_buffer;

   };
}

#endif