#pragma once
#ifndef MainWindow_H
#define MainWindow_H

#include "Win32Framework/Observable.h"
#include "Win32Framework/CustomWindow.h"
#include "Win32Framework/SplitWindow.h"
#include "Win32Framework/CustomWindowBuilder.h"
#include "Win32Framework/ModalDialog.h"
#include "ApplicationSettingsDialog.h"
#include <memory>
#include <functional>
#include <algorithm>
#include <vector>
#include <Windows.h>

class MainWindowListener
{
public:
   virtual void OnAbout() = 0;
   virtual void OnSettings() = 0;
   virtual void OnExit() = 0;
   virtual void OnClose() = 0;
};

class MainWindow : public CustomWindow, public Observable<MainWindowListener>
{
   friend class CustomWindowBuilder<MainWindow>;
public:
   static std::unique_ptr<MainWindow> Create(HINSTANCE hInstance);

   LRESULT CALLBACK ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);

   ModalDialog CreateAboutDialog();
   ApplicationSettingsDialog CreateApplicationSettingsDialog();

private:
   static const int splitterPercentage = 30;
   MainWindow() : CustomWindow() {}

   void OnCreate();
   LRESULT OnCommand(WPARAM wParam, LPARAM lParam);
   LRESULT OnClose(WPARAM wParam, LPARAM lParam);

   void OnSize(int cx, int cy);

   std::unique_ptr<SplitWindow> splitWindow;
};

#endif
