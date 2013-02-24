#include "../../stdafx.h"
#include "ConfigPane.h"
#include "../../Utils/StringResource.h"
#include "../../resource.h"

std::unique_ptr<ConfigPane> ConfigPane::Create(HINSTANCE hInstance, const Window& parent)
{
   return WindowFactory<ConfigPane>(hInstance)
      .ClassName(StringResource(IDC_CONFIGPANE))
      .Style(WS_CHILD | WS_VISIBLE)
      .Parent(parent)
      .Position(0, 0, 200, 100)
      .Create();
}

LRESULT CALLBACK ConfigPane::ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
   switch (message) {
   case WM_CREATE:
      OnCreate();
      break;
   }

   return Window::ProcessMessage(message, wParam, lParam);
}

void ConfigPane::OnCreate()
{
   child = WindowFactory<Window>(GetInstance())
      .ClassName("STATIC")
      .Style(WS_CHILD | WS_VISIBLE)
      .Parent(*this)
      .Title("Some Button")
      .Position(20, 20, 50, 50)
      .Create();
}