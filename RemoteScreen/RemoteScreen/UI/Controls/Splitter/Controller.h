#pragma once
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../../Windows/WindowController.h"
#include "../../CanvasTools.h"

namespace Splitter
{
   class Controller : public WindowController
   {
   public:
      Controller(WindowHandle window, CREATESTRUCT* createStruct);
      LRESULT ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);
   private:
      void Size (int cx, int cy);
      void Paint ();

      void LButtonDown (POINTS pt);
      void LButtonUp (POINTS pt);
      void LButtonDrag (POINTS pt);
      void CaptureChanged ();

      WindowHandle parent;

      int cx;
      int cy;

      int dragStart;
      int dragX;
      Pens3d pens;

      bool dragStarted;
   };
};

#endif