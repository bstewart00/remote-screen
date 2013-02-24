#pragma once
#ifndef Splitter_H
#define Splitter_H

#include "../Windows/Window.h"
#include "../Windows/WindowBuilder.h"
#include "../CanvasTools.h"
#include <memory>
#include <Windows.h>

class Splitter : public Window<>
{
   friend class WindowBuilder<Splitter>;
public:
   static std::unique_ptr<Splitter> Create(HINSTANCE hInstance, const Window& parent, int splitterSize = 8);

   LRESULT CALLBACK ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);
   int GetSize() const { return splitterSize; }

private:
   Splitter(int splitterSize) : Window(), splitterSize(splitterSize) {}

   void OnCreate();
   LRESULT OnCommand(WPARAM wParam, LPARAM lParam);

   void Size(int width, int height);
   void Paint();

   void LButtonDown(POINTS pt);
   void LButtonUp(POINTS pt);
   void LButtonDrag(POINTS pt);
   void CaptureChanged();

   int splitterSize;
   int width;
   int height;

   int dragStart;
   int dragX;
   Pens3d pens;

   bool dragStarted;
};

#endif