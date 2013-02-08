#pragma once
#ifndef WINDOWFACTORY_H
#define WINDOWFACTORY_H

#include "WindowClass.h"
#include "WindowHandle.h"

class WindowFactory
{
public:
   WindowFactory(const WindowClass wndClass);
   WindowHandle Create();
   WindowHandle Create(HINSTANCE hInstance);
   static WindowHandle CreateChild(const WindowHandle& parent, const WindowClass wndClass);
   static WindowHandle CreateDefaultChild(const WindowHandle& parent, std::string className, HINSTANCE hInstance);

   void SetTitle(std::string caption) { titleCaption = caption; }
   void SetPosition(int x, int y, int width, int height);
   void AddExtendedStyle(int flags) { exStyle |= flags; }
   void AddStyle(int flags) { style |= flags; }
   void SetParent(const WindowHandle& parent) { hWndParent = parent; }
protected:
   const WindowClass wndClass;
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

#endif