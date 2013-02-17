#pragma once
#ifndef MainPresenter_H
#define MainPresenter_H

#include "../Views/MainWindow.h"
#include "../../Models/Model.h"

class MainPresenter : private MainWindowListener
{
public:
   MainPresenter(MainWindow& view, Model& model, HINSTANCE hInstance);

private:
   void OnAbout() const;
   void OnEdit() const;
   void OnExit() const;
   void OnDestroy() const;

   MainWindow& view;
   Model& model;
   HINSTANCE hInstance;
};

#endif