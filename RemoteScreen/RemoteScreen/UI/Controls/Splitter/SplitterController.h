#pragma once
#ifndef SPLITTERCONTROLLER_H
#define SPLITTERCONTROLLER_H

#include "../../Windows/WindowController.h"
#include "../../CanvasTools.h"
#include <Windows.h>

class SplitterController : public WindowController
{
public:
   SplitterController(Window window, CREATESTRUCT* createStruct);
   LRESULT SplitterController::ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);
private:
   void Size (int cx, int cy);
   void Paint ();

   void LButtonDown (POINTS pt);
   void LButtonUp (POINTS pt);
   void LButtonDrag (POINTS pt);
   void CaptureChanged ();

   Window parent;

   int cx;
   int cy;

   int dragStart;
   int dragX;
   Pens3d pens;

   bool dragStarted;
};

#endif