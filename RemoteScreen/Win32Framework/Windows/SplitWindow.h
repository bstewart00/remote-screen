#pragma once
#ifndef SplitWindow_H
#define SplitWindow_H

#include "Window.h"
#include "../WindowHandle.h"
#include "Splitter.h"
#include "WindowBuilder.h"
#include <memory>
#include <Windows.h>

class SplitWindow : public Window
{
   friend class WindowBuilder<SplitWindow>;
public:
   static std::unique_ptr<SplitWindow> Create(HINSTANCE hInstance, const WindowHandle& parent, std::unique_ptr<WindowHandle>&& left, std::unique_ptr<WindowHandle>&& right, int splitterPercentage);

   LRESULT CALLBACK ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);

   const WindowHandle& GetFirst() const
   {
      return *leftWin;
   }

   const WindowHandle& GetSecond() const
   {
      return *rightWin;
   }

private:
   SplitWindow(std::unique_ptr<WindowHandle>& left, std::unique_ptr<WindowHandle>& right, int splitterPercentage) : Window(),
      leftWin(std::move(left)),
      rightWin(std::move(right)),
      splitRatioPercentage(splitterPercentage) {}

   void OnCreate();
   LRESULT OnCommand(WPARAM wParam, LPARAM lParam);

   void OnSize(int cx, int cy);
   void MoveSplitter(int x);
   int CalculateSplitterPercentage(int splitterX);
   int CalculateSplitterX();

   std::unique_ptr<WindowHandle> leftWin;
   std::unique_ptr<WindowHandle> rightWin;
   std::unique_ptr<Splitter> splitter;

   int width;
   int height;
   int splitRatioPercentage;
};

#endif
