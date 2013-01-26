#include "Splitter.h"
#include "SplitterController.h"
#include "../../Windows/WindowController.h"
#include "../../Windows/WindowFactory.h"

Window Splitter::RegisterAndCreate(Window parent, HINSTANCE hInstance)
{
   WindowClass wndClass(WindowController::WndProc<SplitterController>, WINDOW_CLASS_NAME, hInstance);
   wndClass.SetSysCursor(IDC_SIZEWE);
   wndClass.SetBgSysColor(COLOR_3DFACE);
   wndClass.Register();

   WindowFactory wndFactory(wndClass);
   wndFactory.AddStyle(WS_CHILD | WS_VISIBLE);
   wndFactory.SetParent(parent);

   return wndFactory.Create();
}