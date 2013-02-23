#include "../../stdafx.h"
#include "ContentPane.h"
#include "../../Utils/StringResource.h"
#include "../../resource.h"

std::unique_ptr<ContentPane> ContentPane::Create(HINSTANCE hInstance, const Window& parent)
{
   WindowFactory<ContentPane> factory(hInstance);
   return factory.Create(StringResource(IDC_CONTENTPANE), WS_CHILD | WS_VISIBLE, parent, "", 0, 0, 200, 100);
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
   HINSTANCE hInstance = GetInstance();

   WindowFactory<Window> factory(hInstance);
   child = factory.Create("STATIC", WS_CHILD | WS_VISIBLE, hWnd, "Some Button", 20, 20, 50, 50);
}