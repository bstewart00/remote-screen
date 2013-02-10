#pragma once
#ifndef MainWindow_H
#define MainWindow_H

#include "../Windows/Window.h"
#include <memory>

class MainWindow : public Window
{
public:
   MainWindow() : Window() {}
   MainWindow(HWND hwnd) : Window(hwnd) {}
   MainWindow(const MainWindow& obj) : Window(obj) {}

   static std::unique_ptr<MainWindow> Create(HINSTANCE hInstance);
   LRESULT CALLBACK ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);

private:
   void OnCreate();
   LRESULT OnCommand(WPARAM wParam, LPARAM lParam);

   void ShowAboutDialog();
   void ShowEditDialog();
   void OnSize(int cx, int cy);
   void MoveSplitter(int x);

   std::unique_ptr<Window> leftWin;
   std::unique_ptr<Window> rightWin;
   std::unique_ptr<Window> splitter;
};

#endif