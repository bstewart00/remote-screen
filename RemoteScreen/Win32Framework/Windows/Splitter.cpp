#include "Splitter.h"
#include "../Canvas.h"
#include "../CustomMessages.h"

namespace Win32
{
   std::unique_ptr<Splitter> Splitter::Create(HINSTANCE hInstance, const WindowHandle& parent, int splitterSize)
   {
      return WindowBuilder<Splitter>(hInstance)
         .ClassName("Splitter")
         .Style(WS_CHILD | WS_VISIBLE)
         .Parent(parent)
         .CursorFromSystem(IDC_SIZEWE)
         .Background(COLOR_3DFACE)
         .Register()
         .Create(splitterSize);
   }

   LRESULT CALLBACK Splitter::ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam)
   {
      switch(message) {
      case WM_SIZE:
         Size(LOWORD(lParam), HIWORD(lParam));
         return 0;
      case WM_PAINT:
         Paint();
         return 0;
      case WM_LBUTTONDOWN:
         LButtonDown(MAKEPOINTS(lParam));
         return 0;
      case WM_LBUTTONUP:
         LButtonUp(MAKEPOINTS(lParam));
         return 0;
      case WM_MOUSEMOVE:
         if(wParam & MK_LBUTTON)
            LButtonDrag(MAKEPOINTS(lParam));
         return 0;
      case WM_CAPTURECHANGED:
         CaptureChanged();
         return 0;
      }

      return Window::ProcessMessage(message, wParam, lParam);
   }

   void Splitter::Size(int width, int height)
   {
      this->width = width;
      this->height = height;
   }

   void Splitter::Paint()
   {
      PaintCanvas canvas(*this);
      canvas.Line(0, 0, 0, height - 1, pens.Light());
      canvas.Line(1, 0, 1, height - 1, pens.Hilight());
      canvas.Line(width - 2, 0, width - 2, height - 1, pens.Shadow());
      canvas.Line(width - 1, 0, width - 1, height - 1, pens.DkShadow());
   }

   void Splitter::LButtonDown(POINTS pt)
   {
      dragStarted = true;

      WindowHandle parent = GetParent();

      CaptureMouse();
      // Find x offset of splitter
      // with respect to parent client area
      POINT ptOrg = {0, 0 };
      parent.ClientToScreen(ptOrg);
      int xParent = ptOrg.x;
      ptOrg.x = 0;
      ClientToScreen(ptOrg);
      int xChild = ptOrg.x;

      dragStart = xChild - xParent + width / 2 - pt.x;

      dragX = dragStart + pt.x;

      // Draw a divider using XOR mode
      UpdateCanvas canvas(parent);
      ModeSetter mode(canvas, R2_NOTXORPEN);
      canvas.Line(dragX, 0, dragX, height - 1);
   }

   void Splitter::LButtonDrag(POINTS pt)
   {
      if (dragStarted) {
         WindowHandle parent = GetParent();

         // Erase previous divider and draw new one
         UpdateCanvas canvas(parent);
         ModeSetter mode(canvas, R2_NOTXORPEN);
         canvas.Line(dragX, 0, dragX, height - 1);
         dragX = dragStart + pt.x;
         canvas.Line(dragX, 0, dragX, height - 1);
      }
   }

   void Splitter::LButtonUp(POINTS pt)
   {
      if (dragStarted) {
         WindowHandle parent = GetParent();

         dragStarted = false;

         ::ReleaseCapture();
         parent.SendMsg(MSG_MOVESPLITTER, dragStart + pt.x);
      }
   }

   void Splitter::CaptureChanged()
   {
      WindowHandle parent = GetParent();

      // We are losing capture
      // End drag selection -- for whatever reason
      // Erase previous divider
      UpdateCanvas canvas(parent);
      ModeSetter mode(canvas, R2_NOTXORPEN);
      canvas.Line(dragX, 0, dragX, height - 1);
   }
}