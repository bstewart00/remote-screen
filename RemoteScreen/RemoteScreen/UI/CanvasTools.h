#pragma once
#if !defined (CANVTOOLS_H)
#define CANVTOOLS_H
#include <Windows.h>

class StockObject
{
public:
   StockObject (HDC hdc, int type)
      : _hdc (hdc)
   {
      _hObjOld = ::SelectObject (_hdc, GetStockObject (type));
   }

   ~StockObject ()
   {
      ::SelectObject (_hdc, _hObjOld);
   }
private:
   HGDIOBJ  _hObjOld;
   HDC      _hdc;
};

class WhitePen : public StockObject
{
public:
   WhitePen (HDC hdc): StockObject (hdc, WHITE_PEN) {}
};

class BlackPen : public StockObject
{
public:
   BlackPen (HDC hdc): StockObject (hdc, BLACK_PEN) {}
};

class Pen
{
public:
   Pen (COLORREF color, int style = PS_SOLID)
   {
      _hPen = ::CreatePen (style, 0, color);
   }
   ~Pen ()
   {
      ::DeleteObject (_hPen);
   }
   operator HPEN () { return _hPen; }
private:
   HPEN    _hPen;
};

class PenHolder
{
public:
   PenHolder (HDC hdc, HPEN hPen)
      : _hdc (hdc)
   {
      _hPenOld = (HPEN) ::SelectObject (_hdc, hPen); 
   }
   ~PenHolder ()
   {
      ::SelectObject (_hdc, _hPenOld);
   }
private:
   HDC     _hdc;
   HPEN    _hPenOld;
};

class ColorPen
{
public:
   ColorPen (HDC hdc, COLORREF color)
      : _hdc (hdc)
   {
      _hPen = ::CreatePen (PS_SOLID, 0, color);
      _hPenOld = (HPEN)::SelectObject (_hdc, _hPen); 
   }
   ~ColorPen ()
   {
      ::SelectObject (_hdc, _hPenOld);
      ::DeleteObject (_hPen);
   }
private:
   HDC     _hdc;
   HPEN    _hPen;
   HPEN    _hPenOld;
};

class ModeSetter
{
public:
   ModeSetter (HDC hdc, int mode = R2_COPYPEN)
      : _hdc (hdc)
   {
      _modeOld = ::GetROP2 (_hdc);
      ::SetROP2 (_hdc, mode);
   }
   ~ModeSetter ()
   {
      ::SetROP2 (_hdc, _modeOld);
   }
private:
   HDC _hdc;
   int _modeOld;
};

#endif

class Pens3d
{
public:
   Pens3d ()
      : _penLight (GetSysColor (COLOR_3DLIGHT)),
      _penHilight (GetSysColor (COLOR_3DHILIGHT)),
      _penShadow (GetSysColor (COLOR_3DSHADOW)),
      _penDkShadow (GetSysColor (COLOR_3DDKSHADOW))
   {}
   Pen & Hilight () { return _penHilight; }
   Pen & Light () { return _penLight; }
   Pen & Shadow () { return _penShadow; }
   Pen & DkShadow () { return _penDkShadow; }
private:
   Pen		_penHilight;
   Pen		_penLight;
   Pen		_penShadow;
   Pen		_penDkShadow;
};