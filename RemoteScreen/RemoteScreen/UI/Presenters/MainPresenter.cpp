#include "MainPresenter.h"

MainPresenter::MainPresenter(MainWindow& view, Model& model)
   : view(view), model(model)
{
   view.AddListener(this);
}

void MainPresenter::OnAboutDialog() const
{
   ::MessageBox(view, L"ABOUT", L"CAPT", MB_OK);
}

void MainPresenter::OnEditDialog() const
{
   ::MessageBox(view, L"EDIT", L"CAPT", MB_OK);
}

void MainPresenter::OnExit() const
{
   ::MessageBox(view, L"EXIT", L"CAPT", MB_OK);
}
