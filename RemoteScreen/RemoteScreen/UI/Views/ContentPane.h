#pragma once
#ifndef ContentPane_H
#define ContentPane_H

#include "Win32Framework/Windows/Window.h"
#include "Win32Framework/Windows/WindowBuilder.h"
#include <memory>
#include <Windows.h>

class ContentPane : public Win32::Window
{
   friend class Win32::WindowBuilder<ContentPane>;
public:
   static std::unique_ptr<ContentPane> Create(HINSTANCE hInstance, const Window& parenti);

   LRESULT CALLBACK ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);

private:
   ContentPane() : Window() {}

   void OnCreate();
   void OnPaint() const;
   LRESULT OnCommand(WPARAM wParam, LPARAM lParam);
   void OnResize() const;
};

#endif