#pragma once
#ifndef CONTROLS_H
#define CONTROLS_H

#include <Windows.h>
#include <boost/nowide/convert.hpp>

class Control
{
public:
   Control(HWND hwndParent, int id)
      : hWnd(GetDlgItem(hwndParent, id))
   {}

   void SetFocus()
   {
      ::SetFocus(hWnd);
   }

   static BOOL IsClicked(int code)
   {
      return code == BN_CLICKED;
   }

   operator HWND() const { return hWnd; }

   void Enable()
   {
      ::EnableWindow(hWnd, TRUE);
   }

   void Disable()
   {
      ::EnableWindow(hWnd, FALSE);
   }

   void SetFont(HFONT font)
   {
      ::SendMessage(hWnd, WM_SETFONT,(WPARAM) font, MAKELPARAM(TRUE, 0));
   }
protected:
   HWND hWnd;
};


class Edit: public Control
{
public:
   Edit(HWND hwndParent, int id)
      : Control(hwndParent, id)
   {}

   void SetString(std::string text)
   {
      std::wstring wideText = boost::nowide::widen(text);
      ::SendMessage(hWnd, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(wideText.c_str()));
   }

   static BOOL IsChanged(int code)
   { 
      return code == EN_CHANGE;
   }

   int GetLen()
   {
      return ::SendMessage(hWnd, WM_GETTEXTLENGTH, 0, 0);
   }

   void GetString(wchar_t* buf, int len)
   {
      ::SendMessage(hWnd, WM_GETTEXT,(WPARAM) len,(LPARAM) buf);
   }

   void Select()
   {
      ::SendMessage(hWnd, EM_SETSEL, 0, -1);
   }
};

#endif