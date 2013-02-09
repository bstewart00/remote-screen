//#include "../../../stdafx.h"
//#include "Controller.h"
//#include "../../Canvas.h"
//#include "../../../CustomMessages.h"
//#include <cstdlib>
//
//namespace Splitter
//{
//   Controller::Controller(Window window, CREATESTRUCT* createStruct)
//      : WindowController(window, createStruct), parent(createStruct->hwndParent)
//   {
//   }
//
//   LRESULT Controller::ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam)
//   {
//      switch(message) {
//      case WM_SIZE:
//         Size(LOWORD(lParam), HIWORD(lParam));
//         return 0;
//      case WM_PAINT:
//         Paint();
//         return 0;
//      case WM_LBUTTONDOWN:
//         LButtonDown(MAKEPOINTS(lParam));
//         return 0;
//      case WM_LBUTTONUP:
//         LButtonUp(MAKEPOINTS(lParam));
//         return 0;
//      case WM_MOUSEMOVE:
//         if(wParam & MK_LBUTTON)
//            LButtonDrag(MAKEPOINTS(lParam));
//         return 0;
//      case WM_CAPTURECHANGED:
//         CaptureChanged();
//         return 0;
//      default:
//         return WindowController::ProcessMessage(message, wParam, lParam);
//      }
//
//      return 0;
//   }
//
//   void Controller::Size(int cx, int cy)
//   {
//      this->cx = cx;
//      this->cy = cy;
//   }
//
//   void Controller::Paint()
//   {
//      PaintCanvas canvas(window);
//      canvas.Line(0, 0, 0, cy - 1, pens.Light());
//      canvas.Line(1, 0, 1, cy - 1, pens.Hilight());
//      canvas.Line(cx - 2, 0, cx - 2, cy - 1, pens.Shadow());
//      canvas.Line(cx - 1, 0, cx - 1, cy - 1, pens.DkShadow());
//   }
//
//   void Controller::LButtonDown(POINTS pt)
//   {
//      dragStarted = true;
//
//      window.CaptureMouse();
//      // Find x offset of splitter
//      // with respect to parent client area
//      POINT ptOrg = {0, 0 };
//      parent.ClientToScreen(ptOrg);
//      int xParent = ptOrg.x;
//      ptOrg.x = 0;
//      window.ClientToScreen(ptOrg);
//      int xChild = ptOrg.x;
//
//      dragStart = xChild - xParent + cx / 2 - pt.x;
//
//      dragX = dragStart + pt.x;
//
//      // Draw a divider using XOR mode
//      UpdateCanvas canvas(parent);
//      ModeSetter mode(canvas, R2_NOTXORPEN);
//      canvas.Line(dragX, 0, dragX, cy - 1);
//   }
//
//   void Controller::LButtonDrag(POINTS pt)
//   {
//      if (dragStarted) {
//         // Erase previous divider and draw new one
//         UpdateCanvas canvas(parent);
//         ModeSetter mode(canvas, R2_NOTXORPEN);
//         canvas.Line(dragX, 0, dragX, cy - 1);
//         dragX = dragStart + pt.x;
//         canvas.Line(dragX, 0, dragX, cy - 1);
//      }
//   }
//
//   void Controller::LButtonUp(POINTS pt)
//   {
//      if (dragStarted) {
//         dragStarted = false;
//
//         ::ReleaseCapture();
//         parent.SendMessage(MSG_MOVESPLITTER, dragStart + pt.x);
//      }
//   }
//
//   void Controller::CaptureChanged()
//   {
//      // We are losing capture
//      // End drag selection -- for whatever reason
//      // Erase previous divider
//      UpdateCanvas canvas(parent);
//      ModeSetter mode(canvas, R2_NOTXORPEN);
//      canvas.Line(dragX, 0, dragX, cy - 1);
//
//   }
//};