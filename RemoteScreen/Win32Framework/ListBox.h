#pragma once
#ifndef ListBox_H
#define ListBox_H

#include "Window.h"
#include "SystemWindow.h"
#include "SystemWindowBuilder.h"
#include <Windows.h>
#include <vector>
#include <string>
#include <memory>

class ListBox : public SystemWindow
{
   friend class SystemWindowBuilder<ListBox>;
public:
   static std::unique_ptr<ListBox> Create(HINSTANCE hInstance, const Window<>& parent);

   void AddItem(const std::string text, LPARAM data = 0);
private:
   ListBox(HWND hWnd) : SystemWindow(hWnd) {}
   
   static bool initialized;
   static void Initialize();
   std::vector<wchar_t*> text_buffer;
   
};

#endif