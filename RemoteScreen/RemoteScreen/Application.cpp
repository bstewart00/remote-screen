#include "Application.h"
#include "Utils/StringResource.h"
#include "UI/Views/MainWindow.h"
#include "UI/Presenters/MainPresenter.h"
#include "Models/Model.h"
#include "WindowsException.h"
#include "Resource.h"

Application::Application(HINSTANCE hInstance, int nCmdShow)
   : hInstance(hInstance), nCmdShow(nCmdShow)
{
}

bool Application::Initialize()
{
   StringResource::SetInstance(hInstance);

   return true;
}

int Application::Run()
{
   Initialize();

   Model model;
   std::unique_ptr<Window> view = MainWindow::Create(hInstance);
   MainPresenter presenter(*view, model);
   presenter.Display(nCmdShow);

   HACCEL hAccelTable = LoadAccelerators(StringResource(IDC_REMOTESCREEN));
   MSG msg;
   BOOL bRet;
   while ((bRet = ::GetMessage(&msg, 0, 0, 0)) != 0) {
      if (bRet == -1) {
         throw WindowsException("Unspecified windows error");
      } else if (!::TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
         ::TranslateMessage(&msg);
         ::DispatchMessage(&msg);
      }
   }

   return (int) msg.wParam;
}