#pragma once
#ifndef MainPresenter_H
#define MainPresenter_H

#include "../Views/MainWindow.h"
#include "../Views/MainWindowListener.h"
#include "../../Models/Model.h"

class MainPresenter : private MainWindowListener
{
public:
   MainPresenter(MainWindow& view, Model& model);

private:
   void OnAbout() const;
   void OnEdit() const;
   void OnExit() const;

   MainWindow& view;
   Model& model;
};

#endif