#pragma once
#ifndef MainWindow_H
#define MainWindow_H

#include "Observable.h"
#include "../Windows/Window.h"
#include "MainWindowListener.h"
#include "ModalDialog.h"
#include <memory>
#include <functional>
#include <algorithm>
#include <vector>

class MainWindow : public Window<LRESULT>, public Observable<MainWindowListener>
{
public:
   MainWindow() : Window() {}
   MainWindow(HWND hwnd) : Window(hwnd) {}
   MainWindow(const MainWindow& obj) : Window(obj) {}

   static std::unique_ptr<MainWindow> Create(HINSTANCE hInstance);

   LRESULT CALLBACK ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);

   ModalDialog CreateAboutDialog();

private:
   void OnCreate();
   LRESULT OnCommand(WPARAM wParam, LPARAM lParam);

   void OnSize(int cx, int cy);
   void MoveSplitter(int x);

   std::unique_ptr<Window> leftWin;
   std::unique_ptr<Window> rightWin;
   std::unique_ptr<Window> splitter;
};

#endif