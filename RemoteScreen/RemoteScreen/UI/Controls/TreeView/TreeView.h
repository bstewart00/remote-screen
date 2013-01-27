#pragma once
#ifndef TREEVIEW_H
#define TREEVIEW_H

#include "../../Windows/Window.h"
#include <vector>

class TreeView : public Window
{
public:
   static TreeView Create(const Window& parent, HINSTANCE hInstance);

   void AddItem(const std::string text);
private:
   TreeView(HWND hwnd);

   static bool initialized;
   static void Initialize();
   std::vector<wchar_t*> text_buffer;
   
};

#endif