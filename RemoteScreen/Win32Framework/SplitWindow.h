#pragma once
#ifndef SplitWindow_H
#define SplitWindow_H

#include "Window.h"
#include "Splitter.h"
#include "WindowBuilder.h"
#include <memory>
#include <Windows.h>

class SplitWindow : public Window<>
{
   friend class WindowBuilder<SplitWindow>;
public:
   static std::unique_ptr<SplitWindow> Create(HINSTANCE hInstance, const Window& parent, std::unique_ptr<Window>&& left, std::unique_ptr<Window>&& right, int splitterPercentage);

   LRESULT CALLBACK ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);

   const Window& GetFirst() const
   {
      return *leftWin;
   }

   const Window& GetSecond() const
   {
      return *rightWin;
   }

private:
   SplitWindow(std::unique_ptr<Window>& left, std::unique_ptr<Window>& right, int splitterPercentage) : Window(),
      leftWin(std::move(left)),
      rightWin(std::move(right)),
      splitRatioPercentage(splitterPercentage) {}

   void OnCreate();
   LRESULT OnCommand(WPARAM wParam, LPARAM lParam);

   void OnSize(int cx, int cy);
   void MoveSplitter(int x);
   int CalculateSplitterPercentage(int splitterX);
   int CalculateSplitterX();

   std::unique_ptr<Window> leftWin;
   std::unique_ptr<Window> rightWin;
   std::unique_ptr<Splitter> splitter;

   int width;
   int height;
   int splitRatioPercentage;
};

#endif
