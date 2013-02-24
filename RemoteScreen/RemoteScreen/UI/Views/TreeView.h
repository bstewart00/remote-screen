#pragma once
#ifndef TreeView_H
#define TreeView_H

#include "../Windows/Window.h"
#include "../Windows/SystemWindowBuilder.h"
#include <Windows.h>
#include <vector>
#include <string>
#include <memory>

class TreeView : public Window<>
{
   friend class SystemWindowBuilder<TreeView>;
public:
   static std::unique_ptr<TreeView> Create(HINSTANCE hInstance, const Window& parent);

   void AddItem(const std::string text);
private:
   TreeView(const wchar_t* classAtom) : Window(classAtom) {}

   static bool initialized;
   static void Initialize();
   std::vector<wchar_t*> text_buffer;
   
};

#endif