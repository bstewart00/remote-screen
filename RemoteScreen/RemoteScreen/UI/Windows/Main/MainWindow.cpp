#include "MainWindow.h"

MainWindow::MainWindow(const WindowClass& wndClass, const std::string& windowName)
   : Window(wndClass)
{
   style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
   name = windowName;
}
