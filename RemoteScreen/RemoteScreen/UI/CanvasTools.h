#pragma once
#ifndef CANVASTOOLS_H
#define CANVASTOOLS_H


class StockObject
{
public:
   StockObject(HDC hdc, int type)
      : hdc(hdc)
   {
      hObjOld = ::SelectObject(hdc, GetStockObject (type));
   }

   ~StockObject()
   {
      ::SelectObject(hdc, hObjOld);
   }
private:
   HGDIOBJ  hObjOld;
   HDC      hdc;
};

class WhitePen : public StockObject
{
public:
   WhitePen(HDC hdc): StockObject (hdc, WHITE_PEN) {}
};

class BlackPen : public StockObject
{
public:
   BlackPen(HDC hdc): StockObject (hdc, BLACK_PEN) {}
};

class Pen
{
public:
   Pen(COLORREF color, int style = PS_SOLID)
   {
      hPen = ::CreatePen(style, 0, color);
   }
   ~Pen()
   {
      ::DeleteObject(hPen);
   }
   operator HPEN() const { return hPen; }
private:
   HPEN hPen;
};

class PenContext
{
public:
   PenContext(HDC hdc, HPEN hPen)
      : hdc(hdc)
   {
      hPenOld = reinterpret_cast<HPEN>(::SelectObject(hdc, hPen));
   }
   ~PenContext()
   {
      ::SelectObject(hdc, hPenOld);
   }
private:
   HDC hdc;
   HPEN hPenOld;
};

class ModeSetter
{
public:
   ModeSetter(HDC hdc, int mode = R2_COPYPEN)
      : hdc(hdc)
   {
      modeOld = ::GetROP2(hdc);
      ::SetROP2(hdc, mode);
   }
   ~ModeSetter()
   {
      ::SetROP2(hdc, modeOld);
   }
private:
   HDC hdc;
   int modeOld;
};

class Pens3d
{
public:
   Pens3d()
      : penLight(GetSysColor (COLOR_3DLIGHT)),
      penHilight(GetSysColor (COLOR_3DHILIGHT)),
      penShadow(GetSysColor (COLOR_3DSHADOW)),
      penDkShadow(GetSysColor (COLOR_3DDKSHADOW))
   {}
   const Pen & Hilight() const { return penHilight; }
   const Pen & Light() const { return penLight; }
   const Pen & Shadow() const { return penShadow; }
   const Pen & DkShadow() const { return penDkShadow; }
private:
   Pen penHilight;
   Pen penLight;
   Pen penShadow;
   Pen penDkShadow;
};

#endif