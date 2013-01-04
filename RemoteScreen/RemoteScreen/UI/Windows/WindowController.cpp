#include "WindowController.h"
#include "Window.h"

WindowController::WindowController(Window* window)
   :window(window)
{
}

LRESULT WindowController::ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
   return ::DefWindowProc(*window, message, wParam, lParam);
}