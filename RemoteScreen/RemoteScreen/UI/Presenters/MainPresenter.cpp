#include "MainPresenter.h"

MainPresenter::MainPresenter(Window& view, Model& model)
   : view(view), model(model)
{
}

void MainPresenter::Display(int nCmdShow)
{
   view.Show(nCmdShow);
}