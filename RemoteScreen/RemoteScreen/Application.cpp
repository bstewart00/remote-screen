#include "Application.h"
#include "Utils/StringResource.h"
#include "UI/Windows/Main/MainWindowController.h"
#include "UI/Views/MainWindowView.h"
#include "Resource.h"

Application::Application(HINSTANCE hInstance, int nCmdShow)
   : hInstance(hInstance), nCmdShow(nCmdShow)
{
}

bool Application::Initialize()
{
   StringResource::SetInstance(hInstance);

   MainWindowView view(hInstance);
   view.Display(nCmdShow);

   return true;
}

int Application::Run()
{

   Initialize();

   HACCEL hAccelTable = LoadAccelerators(StringResource(IDC_REMOTESCREEN));
   MSG msg;
   BOOL bRet;
   while ((bRet = ::GetMessage(&msg, NULL, 0, 0)) != 0) {
      if (bRet == -1) {
         return -1;
      } else if (!::TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
         ::TranslateMessage(&msg);
         ::DispatchMessage(&msg);
      }
   }

   return (int) msg.wParam;
}