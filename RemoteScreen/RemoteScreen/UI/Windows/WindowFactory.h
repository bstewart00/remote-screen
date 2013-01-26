#pragma once
#ifndef WINDOWFACTORY_H
#define WINDOWFACTORY_H

#include "WindowClass.h"
#include "Window.h"
#include <Windows.h>

class WindowFactory
{
public:
   WindowFactory(const WindowClass wndClass);
   Window Create();
   Window Create(HINSTANCE hInstance);
   static Window CreateDefaultChild(const Window& parent, std::string className, HINSTANCE hInstance);

   void SetTitle(std::string caption) { titleCaption = caption; }
   void SetPosition(int x, int y, int width, int height);
   void AddExtendedStyle(int flags) { exStyle |= flags; }
   void AddStyle(int flags) { style |= flags; }
   void SetParent(const Window& parent) { hWndParent = parent; }
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