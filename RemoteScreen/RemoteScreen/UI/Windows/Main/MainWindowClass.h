#pragma once
#ifndef MAINWINDOWCLASS_H
#define MAINWINDOWCLASS_H

#include "../../../WindowsException.h"
#include "../WindowClass.h"
#include <Windows.h>
#include <string>

class MainWindowClass : public WindowClass
{
public:
   MainWindowClass(WNDPROC wndProc, std::string name, HINSTANCE hInst, int icon, int iconSmall, int menu);
};

#endif