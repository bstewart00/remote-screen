#pragma once
#ifndef CANVAS_H
#define CANVAS_H

#include <Windows.h>
#include "CanvasTools.h"

class Canvas
{
public:
   operator HDC() const
   { 
      return _hdc; 
   }

   void SetPixel(int x, int y, COLORREF color)
   {
      ::SetPixel(_hdc, x, y, color);
   }

   void MoveTo(int x, int y)
   {
      ::MoveToEx(_hdc, x, y, 0);
   }

   void LineTo(int x, int y)
   {
      ::LineTo(_hdc, x, y);
   }

   void LineTo(int x, int y, const Pen& pen)
   {
      PenContext context(_hdc, pen);
      LineTo(x, y);
   }

   void Line(int x1, int y1, int x2, int y2)
   {
      ::MoveToEx(_hdc, x1, y1, 0);
      LineTo(x2, y2);
   }

   void Line(int x1, int y1, int x2, int y2, const Pen& pen)
   {
      PenContext context(_hdc, pen);
      Line(x1, y1, x2, y2);
   }
protected:
   Canvas(HDC hdc) :_hdc(hdc) {}

   HDC  _hdc;
};

class PaintCanvas: public Canvas
{
public:
   PaintCanvas(HWND hwnd)
      : Canvas(::BeginPaint (hwnd, &_paint)),
      _hwnd(hwnd)
   {}

   ~PaintCanvas()
   {
      ::EndPaint(_hwnd, &_paint);
   }

   int Top() const    { return _paint.rcPaint.top; }
   int Bottom() const { return _paint.rcPaint.bottom; }
   int Left() const   { return _paint.rcPaint.left; }
   int Right() const  { return _paint.rcPaint.right; }

protected:

   PAINTSTRUCT _paint;
   HWND        _hwnd;
};

class UpdateCanvas: public Canvas
{
public:
   UpdateCanvas(HWND hwnd)
      : Canvas(::GetDC(hwnd)),
      _hwnd(hwnd)
   {}

   ~UpdateCanvas()
   {
      ::ReleaseDC(_hwnd, _hdc);
   }

protected:

   HWND _hwnd;
};

#endif
