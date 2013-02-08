#pragma once
#ifndef CONTROLS_H
#define CONTROLS_H

#include "../Windows/WindowHandle.h"

class Control : public WindowHandle
{
public:
   Control(HWND hwndParent, int id)
      : WindowHandle(GetDlgItem(hwndParent, id))
   {}

   static BOOL IsClicked(int code)
   {
      return code == BN_CLICKED;
   }
};


class Edit: public Control
{
public:
   Edit(HWND hwndParent, int id)
      : Control(hwndParent, id)
   {}

   static BOOL IsChanged(int code)
   { 
      return code == EN_CHANGE;
   }
};

#endif