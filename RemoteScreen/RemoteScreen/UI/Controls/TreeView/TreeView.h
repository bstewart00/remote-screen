#pragma once
#ifndef TREEVIEW_H
#define TREEVIEW_H

#include "../../Windows/Window.h"

class TreeView
{
public:
   TreeView(const Window& parent, HINSTANCE hInstance);
   ~TreeView();

   void AddItem();
   void DeleteItem();


private:
   static bool initialized;
   static void Initialize();

   const Window& parent;
   Window treeview;
   HINSTANCE hInstance;
};

#endif