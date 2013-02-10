#pragma once
#ifndef MainWindow_H
#define MainWindow_H

#include "../Windows/Window.h"
#include "MainWindowListener.h"
#include <memory>
#include <functional>
#include <algorithm>
#include <vector>

class MainWindow : public Window
{
public:
   MainWindow() : Window() {}
   MainWindow(HWND hwnd) : Window(hwnd) {}
   MainWindow(const MainWindow& obj) : Window(obj) {}

   static std::unique_ptr<MainWindow> Create(HINSTANCE hInstance);
   LRESULT CALLBACK ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);

   void AddListener(MainWindowListener* listener)
   {
      listeners.push_back(listener);
   }

private:
   void NotifyListeners(void(MainWindowListener::*fn)() const)
   {
      std::for_each(listeners.begin(), listeners.end(), std::bind(fn, std::placeholders::_1));
   }

   void OnCreate();
   LRESULT OnCommand(WPARAM wParam, LPARAM lParam);

   void ShowAboutDialog();
   void ShowEditDialog();
   void OnSize(int cx, int cy);
   void MoveSplitter(int x);

   std::unique_ptr<Window> leftWin;
   std::unique_ptr<Window> rightWin;
   std::unique_ptr<Window> splitter;

   std::vector<MainWindowListener*> listeners;
};

#endif