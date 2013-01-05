#pragma once
#ifndef SPLITTERCONTROLLER_H
#define SPLITTERCONTROLLER_H

#include "../WindowController.h"
#include <Windows.h>

class SplitterController : public WindowController
{
public:
   SplitterController(Window window);

    void Size (int cx, int cy) { cx = cx; cy = cy; }
    void Paint ();

    void LButtonDown (POINTS pt);
    void LButtonUp (POINTS pt);
    void LButtonDrag (POINTS pt);
    void CaptureChanged ();

   friend LRESULT WindowController::WndProc<SplitterController>(HWND, UINT, WPARAM, LPARAM);
private:
   LRESULT SplitterController::ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);

    int cx;
    int cy;

    int dragStart;
    int dragX;
};

#endif