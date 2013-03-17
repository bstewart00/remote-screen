#pragma once
#ifndef TreeView_H
#define TreeView_H

#include "WindowHandle.h"
#include "CommonControlBuilder.h"
#include <Windows.h>
#include <vector>
#include <string>
#include <memory>

class TreeView : public WindowHandle
{
   friend class CommonControlBuilder<TreeView>;
public:
   static std::unique_ptr<TreeView> Create(HINSTANCE hInstance, const WindowHandle& parent);

   void AddItem(const std::string text);
private:
   TreeView(HWND hWnd) : WindowHandle(hWnd) {}

   static bool initialized;
   static void Initialize();
   std::vector<wchar_t*> text_buffer;
   
};

#endif