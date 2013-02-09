#pragma once
#ifndef MainWindow_H
#define MainWindow_H

#include "../Windows/Window.h"

class MainWindow : public Window
{
public:
   static MainWindow Create(HINSTANCE hInstance);
   LRESULT CALLBACK ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);

private:
   void OnCreate();
   LRESULT OnCommand(WPARAM wParam, LPARAM lParam);

   void ShowAboutDialog();
   void ShowEditDialog();
   void OnSize(int cx, int cy);
   void MoveSplitter(int x);
};

#endif