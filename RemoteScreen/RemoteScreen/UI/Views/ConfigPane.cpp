#include "../../stdafx.h"
#include "ConfigPane.h"
#include "../../Utils/StringResource.h"
#include "../../resource.h"

std::unique_ptr<ConfigPane> ConfigPane::Create(HINSTANCE hInstance, const Window& parent)
{
   WindowFactory<ConfigPane> factory(hInstance);
   return factory.Create(StringResource(IDC_CONFIGPANE), WS_CHILD | WS_VISIBLE | WS_BORDER, parent, "", 0, 0, 200, 100);
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
   HINSTANCE hInstance = GetInstance();

   WindowFactory<Window> factory(hInstance);
   child = factory.Create("STATIC", WS_CHILD | WS_VISIBLE | WS_BORDER, hWnd, "Some Button", 20, 20, 50, 50);
}