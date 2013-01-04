#pragma once
#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include "../WindowController.h"

class MainWindowController : public WindowController
{
public:
   MainWindowController(Window* window);

   friend LRESULT WindowController::WndProc<MainWindowController>(HWND, UINT, WPARAM, LPARAM);
private:
   LRESULT MainWindowController::ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);

   static INT_PTR CALLBACK AboutDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
};

#endif