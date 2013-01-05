#pragma once
#ifndef CONTROLS_H
#define CONTROLS_H

#include "../Windows/Window.h"

class Control : public Window
{
public:
   Control(HWND hwndParent, int id)
      : Window(GetDlgItem(hwndParent, id))
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