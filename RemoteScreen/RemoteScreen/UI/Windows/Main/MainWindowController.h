#pragma once
#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include "../WindowController.h"
#include <memory>

class MainWindowController : public WindowController
{
public:
   MainWindowController(WindowHandle window, CREATESTRUCT* createStruct);
   LRESULT ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);
private:
   void OnCreate();
   LRESULT OnCommand(WPARAM wParam, LPARAM lParam);

   void ShowAboutDialog();
   void ShowEditDialog();
   void Size(int cx, int cy);
   void MoveSplitter(int x);

   static const int splitterWidth = 8;

   std::unique_ptr<WindowHandle> leftWin;
   std::unique_ptr<WindowHandle> rightWin;
   WindowHandle splitter;
   int cx;
   int cy;
   int splitRatioPercentage;
};

#endif