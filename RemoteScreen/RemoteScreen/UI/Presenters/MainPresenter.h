#pragma once
#ifndef MainPresenter_H
#define MainPresenter_H

#include "../Views/MainWindow.h"
#include "ConfigPanePresenter.h"
#include "ContentPanePresenter.h"
#include "EventHub.h"
#include "../../Models/ApplicationSettings.h"

class MainPresenter : private MainWindowListener
{
public:
   MainPresenter(MainWindow& view, ApplicationSettings& settings, HINSTANCE hInstance);

private:
   void OnAbout();
   void OnSettings();
   void OnExit();
   void OnClose();

   void ConfirmExit() const;

   EventHub eventHub;
   MainWindow& view;
   ConfigPanePresenter configPanePresenter;
   ContentPanePresenter contentPanePresenter;

   ApplicationSettings& settings;
   HINSTANCE hInstance;
};

#endif