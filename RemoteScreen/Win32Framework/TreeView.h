#pragma once
#ifndef TreeView_H
#define TreeView_H

#include "Window.h"
#include "SystemWindow.h"
#include "SystemWindowBuilder.h"
#include <Windows.h>
#include <vector>
#include <string>
#include <memory>

class TreeView : public SystemWindow
{
   friend class SystemWindowBuilder<TreeView>;
public:
   static std::unique_ptr<TreeView> Create(HINSTANCE hInstance, const Window<>& parent);

   void AddItem(const std::string text);
private:
   TreeView(HWND hWnd) : SystemWindow(hWnd) {}

   static bool initialized;
   static void Initialize();
   std::vector<wchar_t*> text_buffer;
   
};

#endif