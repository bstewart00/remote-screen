#include "../../../stdafx.h"
#include "Splitter.h"
#include "Controller.h"
#include "../../Windows/WindowController.h"
#include "../../Windows/WindowFactory.h"

WindowHandle Splitter::RegisterAndCreate(WindowHandle parent, HINSTANCE hInstance)
{
   WindowClass wndClass(WindowController::WndProc<Splitter::Controller>, WINDOW_CLASS_NAME, hInstance);
   wndClass.SetSysCursor(IDC_SIZEWE);
   wndClass.SetBgSysColor(COLOR_3DFACE);
   wndClass.Register();

   WindowFactory wndFactory(wndClass);
   wndFactory.AddStyle(WS_CHILD | WS_VISIBLE);
   wndFactory.SetParent(parent);

   return wndFactory.Create();
}