#include "../../stdafx.h"
#include "ContentPane.h"
#include "../Windows/SystemWindowBuilder.h"
#include "../../Utils/StringResource.h"
#include "../../resource.h"

std::unique_ptr<ContentPane> ContentPane::Create(HINSTANCE hInstance, const Window& parent)
{
   return WindowBuilder<ContentPane>(hInstance)
      .ClassName(StringResource(IDC_CONTENTPANE))
      .Style(WS_CHILD | WS_VISIBLE)
      .Parent(parent)
      .Position(0, 0, 200, 100)
      .Register()
      .Create();
}

LRESULT CALLBACK ContentPane::ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
   switch (message) {
   case WM_CREATE:
      OnCreate();
      break;
   }

   return Window::ProcessMessage(message, wParam, lParam);
}

void ContentPane::OnCreate()
{
   child = SystemWindowBuilder<Window>(GetInstance())
      .ClassName("STATIC")
      .Style(WS_CHILD | WS_VISIBLE)
      .Parent(*this)
      .Title("Some Button")
      .Position(20, 20, 50, 50)
      .Create();
}