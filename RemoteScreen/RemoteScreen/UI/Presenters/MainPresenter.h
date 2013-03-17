#pragma once
#ifndef MainPresenter_H
#define MainPresenter_H

#include "../Views/MainWindow.h"
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
   void OnCreated();

   void ConfirmExit() const;

   MainWindow& view;
   ApplicationSettings& settings;
   HINSTANCE hInstance;
};

#endif