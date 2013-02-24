#pragma once
#ifndef MainWindow_H
#define MainWindow_H

#include "../../Observable.h"
#include "../Windows/Window.h"
#include "Splitter.h"
#include "../Windows/WindowBuilder.h"
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

class MainWindow : public Window<>, public Observable<MainWindowListener>
{
   friend class WindowBuilder<MainWindow>;
public:
   static std::unique_ptr<MainWindow> Create(HINSTANCE hInstance);

   LRESULT CALLBACK ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);

   ModalDialog CreateAboutDialog();
   ApplicationSettingsDialog CreateApplicationSettingsDialog();

private:
   MainWindow(const wchar_t* classAtom) : Window(classAtom), splitRatioPercentage(30) {}

   void OnCreate();
   LRESULT OnCommand(WPARAM wParam, LPARAM lParam);
   LRESULT OnClose(WPARAM wParam, LPARAM lParam);

   void OnSize(int cx, int cy);
   void MoveSplitter(int x);
   int CalculateSplitterPercentage(int splitterX);
   int CalculateSplitterX();

   std::unique_ptr<Window> leftWin;
   std::unique_ptr<Window> rightWin;
   std::unique_ptr<Splitter> splitter;

   int width;
   int height;
   int splitRatioPercentage;
};

#endif
