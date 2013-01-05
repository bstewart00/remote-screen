#pragma once
#ifndef SPLITTERCLASS_H
#define SPLITTERCLASS_H

#include "../WindowClass.h"

class SplitterClass : public WindowClass
{
public:
   SplitterClass(WNDPROC wndProc, std::string name, HINSTANCE hInst);
};

#endif