#pragma once
#ifndef MainWindow_H
#define MainWindow_H

#include "Common/Observable.h"
#include "Win32Framework/Windows/Window.h"
#include "Win32Framework/Windows/SplitWindow.h"
#include "Win32Framework/Windows/WindowBuilder.h"
#include "Win32Framework/Dialogs/ModalDialog.h"
#include "ApplicationSettingsDialog.h"
#include "ConfigPane.h"
#include "ContentPane.h"
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
   virtual void OnCreated() = 0;
};

class MainWindow : public Win32::Window, public Win32::Observable<MainWindowListener>, private ConfigPaneListener
{
   friend class Win32::WindowBuilder<MainWindow>;
public:
   static std::unique_ptr<MainWindow> Create(HINSTANCE hInstance);

   LRESULT CALLBACK ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);

   Win32::ModalDialog CreateAboutDialog() const;
   ApplicationSettingsDialog CreateApplicationSettingsDialog() const;

   const ConfigPane& GetConfigPane() const
   {
      return dynamic_cast<const ConfigPane&>(splitWindow->GetFirst());
   }

   const ContentPane& GetContentPane() const
   {
      return dynamic_cast<const ContentPane&>(splitWindow->GetSecond());
   }
private:
   static const int splitterPercentage = 30;
   MainWindow() : Window() {}

   void OnCreate();
   LRESULT OnCommand(WPARAM wParam, LPARAM lParam);
   LRESULT OnClose(WPARAM wParam, LPARAM lParam) const;
   void OnMonitorSelected();
   void OnSize(int cx, int cy) const;

   std::unique_ptr<Win32::SplitWindow> splitWindow;
};

#endif
