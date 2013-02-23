#pragma once
#ifndef MainWindow_H
#define MainWindow_H

#include "../../Observable.h"
#include "../Windows/Window.h"
#include "../Windows/WindowFactory.h"
#include "ModalDialog.h"
#include "ApplicationSettingsDialog.h"
#include <memory>
#include <functional>
#include <algorithm>
#include <vector>

class MainWindowListener
{
public:
   virtual void OnAbout() = 0;
   virtual void OnSettings() = 0;
   virtual void OnExit() = 0;
   virtual void OnClose() = 0;
};

class MainWindow : public Window<LRESULT>, public Observable<MainWindowListener>
{
   friend class WindowFactory<MainWindow>;
public:
   static std::unique_ptr<MainWindow> Create(HINSTANCE hInstance);

   LRESULT CALLBACK ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);

   ModalDialog CreateAboutDialog();
   ApplicationSettingsDialog CreateApplicationSettingsDialog();

private:
   MainWindow() : Window() {}

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
