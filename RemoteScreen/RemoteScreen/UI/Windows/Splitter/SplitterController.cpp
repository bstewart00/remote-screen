#include "SplitterController.h"

SplitterController::SplitterController(Window window)
   : WindowController(window)
{
}

LRESULT SplitterController::ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
   switch (message) {
   //case WM_SIZE:
   //   Size (LOWORD(lParam), HIWORD(lParam));
   //   return 0;
   //case WM_PAINT:
   //   Paint ();
   //   return 0;
   //case WM_LBUTTONDOWN:
   //   LButtonDown (MAKEPOINTS (lParam));
   //   return 0;
   //case WM_LBUTTONUP:
   //   LButtonUp (MAKEPOINTS (lParam));
   //   return 0;
   //case WM_MOUSEMOVE:
   //   if (wParam & MK_LBUTTON)
   //      LButtonDrag (MAKEPOINTS (lParam));
   //   return 0;
   //case WM_CAPTURECHANGED:
   //   CaptureChanged ();
   //   return 0;
   default:
      return WindowController::ProcessMessage(message, wParam, lParam);
   }

   return 0;
}
//
//void SplitterController::Paint ()
//{
//    PaintCanvas canvas (_hwnd);
//    {
//        PenHolder pen (canvas, _pens.Light ());
//        canvas.Line (0, 0, 0, _cy - 1);
//    }
//    {
//        PenHolder pen (canvas, _pens.Hilight ());
//        canvas.Line (1, 0, 1, _cy - 1);
//    }
//    {
//        PenHolder pen (canvas, _pens.Shadow ());
//        canvas.Line (_cx - 2, 0, _cx - 2, _cy - 1);
//    }
//    {
//        PenHolder pen (canvas, _pens.DkShadow ());
//        canvas.Line (_cx - 1, 0, _cx - 1, _cy - 1);
//    }
//}
//
//void SplitterController::LButtonDown (POINTS pt)
//{
//    _hwnd.CaptureMouse ();
//    // Find x offset of splitter
//    // with respect to parent client area
//    POINT ptOrg = {0, 0 };
//    _hwndParent.ClientToScreen (ptOrg);
//    int xParent = ptOrg.x;
//    ptOrg.x = 0;
//    _hwnd.ClientToScreen (ptOrg);
//    int xChild = ptOrg.x;
//
//    _dragStart = xChild - xParent + _cx / 2 - pt.x;
//
//    _dragX = _dragStart + pt.x;
//
//    // Draw a divider using XOR mode
//    UpdateCanvas canvas (_hwndParent);
//    ModeSetter mode (canvas, R2_NOTXORPEN);
//    canvas.Line (_dragX, 0, _dragX, _cy - 1);
//
//}
//
//void SplitterController::LButtonDrag (POINTS pt)
//{
//    // Erase previous divider and draw new one
//    UpdateCanvas canvas (_hwndParent);
//    ModeSetter mode (canvas, R2_NOTXORPEN);
//    canvas.Line (_dragX, 0, _dragX, _cy - 1);
//    _dragX = _dragStart + pt.x;
//    canvas.Line (_dragX, 0, _dragX, _cy - 1);
//}
//
//void SplitterController::LButtonUp (POINTS pt)
//{
//    // Calling ReleaseCapture will send us the WM_CAPTURECHANGED
//    _hwnd.ReleaseMouse ();
//    _hwndParent.SendMessage (MSG_MOVESPLITTER, _dragStart + pt.x);
//}
//
//void SplitterController::CaptureChanged ()
//{
//    // We are losing capture
//    // End drag selection -- for whatever reason
//    // Erase previous divider
//    UpdateCanvas canvas (_hwndParent);
//    ModeSetter mode (canvas, R2_NOTXORPEN);
//    canvas.Line (_dragX, 0, _dragX, _cy - 1);
//}
