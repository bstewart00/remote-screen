#include "stdafx.h"
#include "ContentPane.h"
#include "Win32Framework/Controls/CommonControlBuilder.h"
#include "Win32Framework/Utils/StringResource.h"
#include "Win32Framework/Canvas.h"
#include "../../resource.h"
#include "../../Imaging/MonitorImageSource.h"

#include <iostream>

std::unique_ptr<ContentPane> ContentPane::Create(HINSTANCE hInstance, const Window& parent)
{
   return Win32::WindowBuilder<ContentPane>(hInstance)
      .ClassName(Win32::StringResource(IDC_CONTENTPANE))
      .Style(WS_CHILD | WS_VISIBLE)
      .Parent(parent)
      .Register()
      .Create();
}

LRESULT CALLBACK ContentPane::ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
   switch (message) {
   case WM_CREATE:
      OnCreate();
      break;
   case WM_PAINT:
      OnPaint();
      break;
   case WM_SIZE:
      OnResize();
   }

   return Window::ProcessMessage(message, wParam, lParam);
}

void ContentPane::OnCreate()
{

}

void ContentPane::OnPaint() const
{
   MonitorImageSource src;
   src.GetImage();
}

void ContentPane::OnResize() const
{
}