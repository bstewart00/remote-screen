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
};

class MainWindow : public Win32::Window, public Common::Observable<MainWindowListener>, private ConfigPaneListener
{
   friend class Win32::WindowBuilder<MainWindow>;
public:
   MainWindow(HINSTANCE hInstance);

   LRESULT CALLBACK ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);

   Win32::ModalDialog CreateAboutDialog() const;
   ApplicationSettingsDialog CreateApplicationSettingsDialog() const;

   ConfigPane& GetConfigPane() const
   {
      return dynamic_cast<ConfigPane&>(splitWindow->GetFirst());
   }

   ContentPane& GetContentPane() const
   {
      return dynamic_cast<ContentPane&>(splitWindow->GetSecond());
   }
private:
   static const int splitterPercentage = 30;
   MainWindow(const MainWindow &);
   MainWindow& operator=(const MainWindow &);

   void OnCreate();
   LRESULT OnCommand(WPARAM wParam, LPARAM lParam);
   LRESULT OnClose(WPARAM wParam, LPARAM lParam) const;
   void OnMonitorSelected();
   void OnSize(int cx, int cy) const;

   std::unique_ptr<Win32::SplitWindow> splitWindow;
};

#endif
