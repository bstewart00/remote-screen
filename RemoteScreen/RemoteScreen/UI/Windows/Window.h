#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include "WindowClass.h"
#include <Windows.h>
#include <string>
#include <functional>

class Window
{
public:
   Window(const WindowClass& wndClass);

   void Create();
   void Show(int nCmdShow);
   void Destroy();

   operator HWND() const { return hWnd; }
   inline void SetHWND(HWND hwnd) { hWnd = hwnd; }

   template <typename T>
   static inline T GetLongPtr(HWND hwnd, int index)
   {
       return reinterpret_cast<T>(::GetWindowLongPtr(hwnd, index));
   }

   template <typename T>
   inline T GetLongPtr(int index) { return this->GetLongPtr<T>(hWnd, index); }

   template <typename T>
   static inline void SetLongPtr(HWND hwnd, T value, int index)
   {
       ::SetWindowLongPtr(hwnd, index, reinterpret_cast<LONG_PTR>(hwnd, value));
   }

   template <typename T>
   inline void SetLongPtr(T value, int index) { return this->SetLongPtr<T>(hWnd, value, index); }

protected:
   void InvokeBoolFunc(std::function<BOOL(HWND)> func, std::string errorMessage);

   const WindowClass& wndClass;
   HWND hWnd;

   DWORD exStyle;      
   std::string name;
   DWORD style;        
   int x;            
   int y;            
   int width;        
   int height;       
   HWND hWndParent;   
   HMENU hMenu;        
};

#endif