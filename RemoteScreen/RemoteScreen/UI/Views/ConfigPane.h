#pragma once
#ifndef ConfigPane_H
#define ConfigPane_H

#include "../Windows/Window.h"
#include "../Windows/WindowBuilder.h"
#include "TreeView.h"
#include <memory>
#include <Windows.h>
#include <vector>

class ConfigPane : public Window<>
{
   friend class WindowBuilder<ConfigPane>;
public:
   static std::unique_ptr<ConfigPane> Create(HINSTANCE hInstance, const Window& parent);

   LRESULT CALLBACK ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);

private:
   ConfigPane(const wchar_t* classAtom) : Window(classAtom) {}

   void OnCreate();
   LRESULT OnCommand(WPARAM wParam, LPARAM lParam);

   void AddTreeViewItems();
   std::unique_ptr<TreeView> treeview;
   std::vector<DISPLAY_DEVICE> display_devices;

   std::unique_ptr<SystemWindow> child;
};

#endif

//#pragma once
//#ifndef CONFIGPANE_H
//#define CONFIGPANE_H
//
//#include "../Window.h"
//#include "../../Controls/TreeView/TreeView.h"
//#include <memory>
//#include <vector>
//
//class ConfigPane : public Window
//{
//public:
//   static std::unique_ptr<ConfigPane> Create(const Window& parent, HINSTANCE hInstance);
//   void Move(int x, int y, int width, int height) const;
//
//private:
//   ConfigPane(HWND hwnd, TreeView treeview);

//};
//
//#endif