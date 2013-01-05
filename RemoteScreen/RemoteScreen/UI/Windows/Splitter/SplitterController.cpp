#include "SplitterController.h"
#include "../../Canvas.h"
#include "../../../CustomMessages.h"

SplitterController::SplitterController(Window window, CREATESTRUCT* createStruct)
   : WindowController(window, createStruct), parent(createStruct->hwndParent)
{
}

LRESULT SplitterController::ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
   switch (message) {
   case WM_SIZE:
      Size (LOWORD(lParam), HIWORD(lParam));
      return 0;
   case WM_PAINT:
      Paint ();
      return 0;
   case WM_LBUTTONDOWN:
      LButtonDown (MAKEPOINTS (lParam));
      return 0;
   case WM_LBUTTONUP:
      LButtonUp (MAKEPOINTS (lParam));
      return 0;
   case WM_MOUSEMOVE:
      if (wParam & MK_LBUTTON)
         LButtonDrag (MAKEPOINTS (lParam));
      return 0;
   case WM_CAPTURECHANGED:
      CaptureChanged ();
      return 0;
   default:
      return WindowController::ProcessMessage(message, wParam, lParam);
   }

   return 0;
}

void SplitterController::Size (int cx, int cy)
{
   this->cx = cx;
   this->cy = cy;
}

void SplitterController::Paint ()
{
   PaintCanvas canvas (window);
   {
      PenHolder pen (canvas, pens.Light ());
      canvas.Line (0, 0, 0, cy - 1);
   }
   {
      PenHolder pen (canvas, pens.Hilight ());
      canvas.Line (1, 0, 1, cy - 1);
   }
   {
      PenHolder pen (canvas, pens.Shadow ());
      canvas.Line (cx - 2, 0, cx - 2, cy - 1);
   }
   {
      PenHolder pen (canvas, pens.DkShadow ());
      canvas.Line (cx - 1, 0, cx - 1, cy - 1);
   }
}

void SplitterController::LButtonDown (POINTS pt)
{
   window.CaptureMouse ();
   // Find x offset of splitter
   // with respect to parent client area
   POINT ptOrg = {0, 0 };
   parent.ClientToScreen (ptOrg);
   int xParent = ptOrg.x;
   ptOrg.x = 0;
   window.ClientToScreen (ptOrg);
   int xChild = ptOrg.x;

   dragStart = xChild - xParent + cx / 2 - pt.x;

   dragX = dragStart + pt.x;

   // Draw a divider using XOR mode
   UpdateCanvas canvas (parent);
   ModeSetter mode (canvas, R2_NOTXORPEN);
   canvas.Line (dragX, 0, dragX, cy - 1);

}

void SplitterController::LButtonDrag (POINTS pt)
{
   // Erase previous divider and draw new one
   UpdateCanvas canvas (parent);
   ModeSetter mode (canvas, R2_NOTXORPEN);
   canvas.Line (dragX, 0, dragX, cy - 1);
   dragX = dragStart + pt.x;
   canvas.Line (dragX, 0, dragX, cy - 1);
}

void SplitterController::LButtonUp (POINTS pt)
{
   // Calling ReleaseCapture will send us the WM_CAPTURECHANGED
   window.ReleaseMouse ();
   parent.SendMessage (MSG_MOVESPLITTER, dragStart + pt.x);
}

void SplitterController::CaptureChanged ()
{
   // We are losing capture
   // End drag selection -- for whatever reason
   // Erase previous divider
   UpdateCanvas canvas (parent);
   ModeSetter mode (canvas, R2_NOTXORPEN);
   canvas.Line (dragX, 0, dragX, cy - 1);
}
