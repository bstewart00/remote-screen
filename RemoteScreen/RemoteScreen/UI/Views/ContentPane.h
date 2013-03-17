#pragma once
#ifndef ContentPane_H
#define ContentPane_H

#include "Win32Framework/Windows/CustomWindow.h"
#include "Win32Framework/Windows/CustomWindowBuilder.h"
#include <memory>
#include <Windows.h>

class ContentPane : public CustomWindow
{
   friend class CustomWindowBuilder<ContentPane>;
public:
   static std::unique_ptr<ContentPane> Create(HINSTANCE hInstance, const CustomWindow& parenti);

   LRESULT CALLBACK ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);

private:
   ContentPane() : CustomWindow() {}

   void OnCreate();
   void OnPaint() const;
   LRESULT OnCommand(WPARAM wParam, LPARAM lParam);
   void OnResize() const;
};

#endif