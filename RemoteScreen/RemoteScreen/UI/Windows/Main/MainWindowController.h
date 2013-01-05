#pragma once
#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include "../WindowController.h"

class MainWindowController : public WindowController
{
public:
   MainWindowController(Window window, CREATESTRUCT* createStruct);
   LRESULT MainWindowController::ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);
private:
   void ShowAboutDialog();
   void ShowEditDialog();
   void Size(int cx, int cy);
   void MoveSplitter(int x);

   static const int splitterWidth = 8;

   Window			leftWin;
   Window		    rightWin;
   Window			splitter;
   int				cx;
   int				cy;
   int				splitRatioPercentage;
};

#endif