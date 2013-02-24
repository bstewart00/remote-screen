#pragma once
#ifndef ContentPane_H
#define ContentPane_H

#include "../Windows/Window.h"
#include "../Windows/WindowBuilder.h"
#include <memory>
#include <Windows.h>

class ContentPane : public Window<>
{
   friend class WindowBuilder<ContentPane>;
public:
   static std::unique_ptr<ContentPane> Create(HINSTANCE hInstance, const Window& parent);

   LRESULT CALLBACK ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);

private:
   ContentPane(const wchar_t* classAtom) : Window(classAtom) {}

   void OnCreate();
   LRESULT OnCommand(WPARAM wParam, LPARAM lParam);

   std::unique_ptr<SystemWindow> child;
};

#endif