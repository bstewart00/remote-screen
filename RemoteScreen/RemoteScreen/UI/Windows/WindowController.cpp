#include "WindowController.h"
#include "Window.h"

WindowController::WindowController(Window window, CREATESTRUCT* createStruct)
   :window(window)
{
   OnCreate();
}

LRESULT WindowController::ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
   return ::DefWindowProc(window, message, wParam, lParam);
}