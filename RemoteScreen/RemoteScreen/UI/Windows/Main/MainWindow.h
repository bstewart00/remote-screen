#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../../Window.h"
#include "../../WindowClass.h"

class MainWindow : public Window
{
public:
   MainWindow(const WindowClass& wndClass, const std::string& windowName);
};

#endif