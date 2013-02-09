#include "Splitter.h"
#include "Controller.h"
#include "../../Windows/WindowFactory.h"

Window* Splitter::RegisterAndCreate(Window parent, HINSTANCE hInstance)
{
   WindowFactory<Window> wndFactory(hInstance);
   wndFactory.SetSysCursor(IDC_SIZEWE);
   wndFactory.SetBgSysColor(COLOR_3DFACE);

   return wndFactory.Create(WINDOW_CLASS_NAME, WS_CHILD | WS_VISIBLE, parent);
}