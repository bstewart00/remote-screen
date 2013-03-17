#pragma once
#ifndef SystemWindowBuilder_H
#define SystemWindowBuilder_H

#include "../Utils/StringConverter.h"
#include "../WindowsException.h"
#include <string>
#include <memory>
#include <Windows.h>

template<typename TWindow = SystemWindow>
class CommonControlBuilder
{
public:
   CommonControlBuilder(HINSTANCE hInstance) : hInstance(hInstance)
   {
      parent = nullptr;
      className = "";
      title = "";
      x = CW_USEDEFAULT;
      y = CW_USEDEFAULT;
      width = CW_USEDEFAULT;
      height = CW_USEDEFAULT;
      windowStyle = 0;
      menu = nullptr;
   }

   CommonControlBuilder<TWindow>& ClassName(std::string className)
   {
      this->className = className;
      return *this;
   }

   CommonControlBuilder<TWindow>& ClassName(const wchar_t* systemClassName)
   {
      className = StringConverter::ToUtf8(systemClassName);
      return *this;
   }

   CommonControlBuilder<TWindow>& Style(int windowStyle)
   {
      this->windowStyle = windowStyle;
      return *this;
   }

   CommonControlBuilder<TWindow>& Parent(HWND parent)
   {
      this->parent = parent;
      return *this;
   }

   CommonControlBuilder<TWindow>& Title(std::string title)
   {
      this->title = title;
      return *this;
   }

   CommonControlBuilder<TWindow>& Position(int x, int y, int width, int height)
   {
      this->x = x;
      this->y = y;
      this->width = width;
      this->height = height;
      return *this;
   }

   CommonControlBuilder<TWindow>& Menu(HMENU menu)
   {
      this->menu = menu;
      return *this;
   }

   CommonControlBuilder<TWindow>& Id(int id)
   {
      this->menu = reinterpret_cast<HMENU>(id);
      return *this;
   }

   std::unique_ptr<TWindow> Create()
   {
      HWND hWnd = CreateWindowHandle(nullptr);
      return std::unique_ptr<TWindow>(new TWindow(hWnd));
   }

protected:
   HWND CreateWindowHandle(void* data)
   {
      HWND hWnd = ::CreateWindowEx(
         0,
         StringConverter::ToWide(className).c_str(),
         StringConverter::ToWide(title).c_str(),
         windowStyle,
         x, y, width, height,
         parent, menu, hInstance,
         data);

      if (!hWnd)
         throw WindowsException("Window creation failed.");

      return hWnd;
   }

   HINSTANCE hInstance;
   std::string className;
   std::string title;
   int windowStyle;
   int x;
   int y;
   int width;
   int height;
   HWND parent;
   HMENU menu;
};

#endif
