#pragma once
#ifndef MainPresenter_H
#define MainPresenter_H

#include "../Windows/Window.h"
#include "../../Models/Model.h"

class MainPresenter
{
public:
   MainPresenter(Window& view, Model& model);

   void Display(int nCmdShow);

private:
   Window& view;
   Model& model;
};

#endif