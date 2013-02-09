#include "Application.h"
#include "Utils/StringResource.h"
#include "UI/Views/MainWindow.h"
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

   Window* view = MainWindow::Create(hInstance);
   HWND hwnd = view->operator HWND();
   auto test = Window::GetLongPtr<MainWindow*>(hwnd, GWLP_USERDATA);
   view->Show(nCmdShow);

   test = Window::GetLongPtr<MainWindow*>(static_cast<HWND>(*view), GWLP_USERDATA);

   HACCEL hAccelTable = LoadAccelerators(StringResource(IDC_REMOTESCREEN));
   MSG msg;
   BOOL bRet;
   while ((bRet = ::GetMessage(&msg, 0, 0, 0)) != 0) {
      if (bRet == -1) {
         return -1;
      } else if (!::TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
         ::TranslateMessage(&msg);
         ::DispatchMessage(&msg);
      }
   }

   return (int) msg.wParam;
}