#include "MainWindowView.h"

#include "../Windows/WindowFactory.h"
#include "../Windows/Main/MainWindowController.h"
#include "../../Utils/StringResource.h"
#include "../../Resource.h"

MainWindowView::MainWindowView(HINSTANCE hInstance)
   :hInstance(hInstance), window(MakeWindow())
{
}

WindowHandle MainWindowView::MakeWindow()
{
   WindowFactory mainWindowFactory(hInstance);
   mainWindowFactory.SetStyle(CS_HREDRAW | CS_VREDRAW);
   mainWindowFactory.SetMenu(IDC_REMOTESCREEN);
   mainWindowFactory.SetResIcons(IDI_REMOTESCREEN);
   mainWindowFactory.SetWndProc(WindowController::WndProc<MainWindowController>);

   StringResource className = StringResource(hInstance, IDC_REMOTESCREEN);
   mainWindowFactory.SetClassName(className);

   return mainWindowFactory.Create(className, WS_OVERLAPPEDWINDOW | WS_VISIBLE, nullptr, StringResource(hInstance, IDS_APP_TITLE), 0, 0);
}

void MainWindowView::Display(int nCmdShow)
{
   window.Show(nCmdShow);
   window.Update();
}