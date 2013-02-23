#include "stdafx.h"
#include "Application.h"
#include "Utils/StringResource.h"
#include "UI/Views/MainWindow.h"
#include "UI/Presenters/MainPresenter.h"
#include "Models/ApplicationSettings.h"
#include "WindowsException.h"
#include "Resource.h"
#include "Persistence\ApplicationSettingsRepository.h"

Application::Application(HINSTANCE hInstance, int nCmdShow)
   : hInstance(hInstance), nCmdShow(nCmdShow)
{
}

int Application::Run()
{
   StringResource::SetInstance(hInstance);
   ApplicationSettingsRepository settingsRepository;

   ApplicationSettings settings = settingsRepository.Get();
   std::unique_ptr<MainWindow> view = MainWindow::Create(hInstance);
   MainPresenter presenter(*view, settings, hInstance);
   view->Show(nCmdShow);

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