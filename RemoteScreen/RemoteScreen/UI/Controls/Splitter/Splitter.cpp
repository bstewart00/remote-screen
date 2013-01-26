#include "Splitter.h"
#include "SplitterController.h"
#include "../../Windows/WindowController.h"
#include "../../Windows/WindowFactory.h"

//void Splitter::RegisterClass(HINSTANCE hInstance)
//{
//   WindowClass wndClass(WindowController::WndProc<SplitterController>, WINDOW_CLASS_NAME, hInstance);
//   wndClass.SetSysCursor(IDC_SIZEWE);
//   wndClass.SetBgSysColor(COLOR_3DFACE);
//   wndClass.Register();
//}
//
//Window Splitter::Create()
//{
//   WindowFactory wndFactory(WINDOW_CLASS_NAME);
//   splitterFactory.AddStyle(WS_CHILD | WS_VISIBLE);
//   splitterFactory.SetParent(rightWin);
//}