#include "Application.h"
#include "Utils/StringResource.h"
#include "UI/Views/MainWindow.h"
#include "UI/Presenters/MainPresenter.h"
#include "Models/ApplicationSettings.h"
#include "WindowsException.h"
#include "Resource.h"
#include "Persistence\AppDataSettingsProvider.h"

Application::Application(HINSTANCE hInstance, int nCmdShow)
   : hInstance(hInstance), 
   nCmdShow(nCmdShow), 
   settingsProvider(std::unique_ptr<AppDataSettingsProvider>(new AppDataSettingsProvider()))
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

   ApplicationSettings settings = settingsProvider->GetSettings();
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