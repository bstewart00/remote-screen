#pragma once
#ifndef ContentPane_H
#define ContentPane_H

#include "Win32Framework/Window.h"
#include "Win32Framework/WindowBuilder.h"
#include <memory>
#include <Windows.h>

class ContentPane : public Window<>
{
   friend class WindowBuilder<ContentPane>;
public:
   static std::unique_ptr<ContentPane> Create(HINSTANCE hInstance, const Window& parenti);

   LRESULT CALLBACK ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);

private:
   ContentPane() : Window() {}

   void OnCreate();
   LRESULT OnCommand(WPARAM wParam, LPARAM lParam);
   void OnResize() const;

   std::unique_ptr<SystemWindow> child;
};

#endif