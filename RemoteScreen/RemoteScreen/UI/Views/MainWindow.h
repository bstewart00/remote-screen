#pragma once
#ifndef MainWindow_H
#define MainWindow_H

#include "../../Observable.h"
#include "../Windows/Window.h"
#include "ModalDialog.h"
#include "ApplicationSettingsDialog.h"
#include <memory>
#include <functional>
#include <algorithm>
#include <vector>

class MainWindowListener
{
public:
   virtual void OnAbout() const = 0;
   virtual void OnEdit() const = 0;
   virtual void OnExit() const = 0;
   virtual void OnClose() const = 0;
};

class MainWindow : public Window<LRESULT>, public Observable<MainWindowListener>
{
public:
   MainWindow() : Window() {}
   MainWindow(HWND hwnd) : Window(hwnd) {}
   MainWindow(const MainWindow& obj) : Window(obj) {}

   static std::unique_ptr<MainWindow> Create(HINSTANCE hInstance);

   LRESULT CALLBACK ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);

   ModalDialog CreateAboutDialog();
   ApplicationSettingsDialog CreateApplicationSettingsDialog();

private:
   void OnCreate();
   LRESULT OnCommand(WPARAM wParam, LPARAM lParam);
   LRESULT OnClose(WPARAM wParam, LPARAM lParam);

   void OnSize(int cx, int cy);
   void MoveSplitter(int x);

   std::unique_ptr<Window> leftWin;
   std::unique_ptr<Window> rightWin;
   std::unique_ptr<Window> splitter;
};

#endif
