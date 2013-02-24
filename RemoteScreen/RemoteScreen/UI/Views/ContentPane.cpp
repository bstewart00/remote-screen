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
      .Register()
      .Create();
}

LRESULT CALLBACK ContentPane::ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
   switch (message) {
   case WM_CREATE:
      OnCreate();
      break;
   case WM_SIZE:
      OnResize();
   }

   return Window::ProcessMessage(message, wParam, lParam);
}

void ContentPane::OnCreate()
{
   child = SystemWindowBuilder<>(GetInstance())
      .ClassName("STATIC")
      .Style(WS_CHILD | WS_VISIBLE)
      .Parent(*this)
      .Title("Some Button")
      .Position(20, 20, 50, 50)
      .Create();
}

void ContentPane::OnResize() const
{
   child->Move(100, 100, 200, 200);
}