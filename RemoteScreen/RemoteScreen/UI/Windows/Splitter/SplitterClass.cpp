#include "SplitterClass.h"

SplitterClass::SplitterClass(WNDPROC wndProc, std::string className, HINSTANCE hInst)
   : WindowClass(wndProc, className, hInst)
{
	SetSysCursor(IDC_SIZEWE);
	SetBgSysColor(COLOR_BTNFACE);
}