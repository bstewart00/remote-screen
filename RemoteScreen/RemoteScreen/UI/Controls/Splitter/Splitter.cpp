#include "Splitter.h"
#include "Controller.h"
#include "../../Windows/WindowController.h"
#include "../../Windows/WindowFactory.h"

WindowHandle Splitter::RegisterAndCreate(WindowHandle parent, HINSTANCE hInstance)
{
   WindowFactory wndFactory(hInstance);
   wndFactory.SetSysCursor(IDC_SIZEWE);
   wndFactory.SetBgSysColor(COLOR_3DFACE);
   wndFactory.SetWndProc(WindowController::WndProc<Splitter::Controller>);

   return wndFactory.Create(WINDOW_CLASS_NAME, WS_CHILD | WS_VISIBLE, parent);
}