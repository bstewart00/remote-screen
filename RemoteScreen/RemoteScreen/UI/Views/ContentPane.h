#pragma once
#ifndef ContentPane_H
#define ContentPane_H

#include "../Windows/Window.h"
#include "../Windows/WindowFactory.h"
#include <memory>

class ContentPane : public Window<>
{
   friend class WindowFactory<ContentPane>;
public:
   static std::unique_ptr<ContentPane> Create(HINSTANCE hInstance, const Window& parent);

   LRESULT CALLBACK ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);

private:
   ContentPane() : Window() {}

   void OnCreate();
   LRESULT OnCommand(WPARAM wParam, LPARAM lParam);

   std::unique_ptr<Window> child;
};

#endif