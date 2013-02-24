#pragma once
#ifndef ConfigPane_H
#define ConfigPane_H

#include "../Windows/Window.h"
#include "../Windows/WindowBuilder.h"
#include <memory>

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

   std::unique_ptr<Window> child;
};

#endif