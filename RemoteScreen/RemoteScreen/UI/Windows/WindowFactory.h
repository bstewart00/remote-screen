#pragma once
#ifndef WINDOWFACTORY_H
#define WINDOWFACTORY_H

#include "WindowClass.h"
#include "Window.h"
#include <Windows.h>

class WindowFactory
{
public:
   WindowFactory(const WindowClass& wndClass);
   Window Create();
   void SetTitle(std::string caption) { titleCaption = caption; }
   void SetPosition(int x, int y, int width, int height);
   void AddSysMenu() { style |= WS_SYSMENU; }
   void AddVScrollBar() { style |= WS_VSCROLL; }
   void AddHScrollBar() { style |= WS_HSCROLL; }
   void AddDlgBorder() { style |= WS_DLGFRAME; }
   void AddBorder() { style |= WS_BORDER; }
   void AddTitleBar() { style |= WS_CAPTION; }

protected:
   const WindowClass& wndClass;
   HWND hWnd;

   DWORD exStyle;      
   std::string titleCaption;
   DWORD style;        
   int x;            
   int y;            
   int width;        
   int height;       
   HWND hWndParent;   
   HMENU hMenu;        
};

class MainWindowFactory : public WindowFactory
{
public:
    MainWindowFactory(const WindowClass& wndClass, std::string titleCaption);
};

class ChildWindowFactory: public WindowFactory
{
public:
    ChildWindowFactory(const WindowClass& wndClass, Window parent);
};

#endif