#pragma once
#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include "../WindowController.h"
#include <memory>

class MainWindowController : public WindowController
{
public:
   MainWindowController(Window window, CREATESTRUCT* createStruct);
   LRESULT ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);
private:
   void OnCreate();
   LRESULT OnCommand(WPARAM wParam, LPARAM lParam);

   void ShowAboutDialog();
   void ShowEditDialog();
   void Size(int cx, int cy);
   void MoveSplitter(int x);

   static const int splitterWidth = 8;

   std::unique_ptr<Window> leftWin;
   std::unique_ptr<Window> rightWin;
   Window splitter;
   int cx;
   int cy;
   int splitRatioPercentage;
};

#endif