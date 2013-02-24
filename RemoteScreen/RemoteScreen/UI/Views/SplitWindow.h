#pragma once
#ifndef SplitWindow_H
#define SplitWindow_H

#include "../../Observable.h"
#include "../Windows/Window.h"
#include "Splitter.h"
#include "../Windows/WindowBuilder.h"
#include "ModalDialog.h"
#include "ApplicationSettingsDialog.h"
#include <memory>
#include <functional>
#include <algorithm>
#include <vector>
#include <Windows.h>

class SplitWindow : public Window<>
{
   friend class WindowBuilder<SplitWindow>;
public:
   static std::unique_ptr<SplitWindow> Create(HINSTANCE hInstance, std::shared_ptr<Window> left, std::shared_ptr<Window> right, int splitterPercentage);

   LRESULT CALLBACK ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);

   ModalDialog CreateAboutDialog();
   ApplicationSettingsDialog CreateApplicationSettingsDialog();

private:
   SplitWindow(std::shared_ptr<Window> left, std::shared_ptr<Window> right, int splitterPercentage) : Window(),
      leftWin(std::move(left)),
      rightWin(std::move(right)),
      splitRatioPercentage(splitterPercentage) {}

   void OnCreate();
   LRESULT OnCommand(WPARAM wParam, LPARAM lParam);

   void OnSize(int cx, int cy);
   void MoveSplitter(int x);
   int CalculateSplitterPercentage(int splitterX);
   int CalculateSplitterX();

   std::shared_ptr<Window> leftWin;
   std::shared_ptr<Window> rightWin;
   std::unique_ptr<Splitter> splitter;

   int width;
   int height;
   int splitRatioPercentage;
};

#endif
