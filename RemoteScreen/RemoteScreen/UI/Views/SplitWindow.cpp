#include "../../stdafx.h"
#include "SplitWindow.h"
#include "Splitter.h"
#include "../Windows/WindowBuilder.h"
#include "../../CustomMessages.h"

std::unique_ptr<SplitWindow> SplitWindow::Create(HINSTANCE hInstance, std::shared_ptr<Window> left, std::shared_ptr<Window> right, int splitterPercentage)
{
   return WindowBuilder<SplitWindow>(hInstance)
      .ClassName("SplitWindow")
      .Style(WS_CHILD | WS_VISIBLE)
      .Register()
      .Create(left, right, splitterPercentage);
}

LRESULT CALLBACK SplitWindow::ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
   switch (message) {
   case WM_CREATE:
      OnCreate();
      break;
   case WM_COMMAND:
      return OnCommand(wParam, lParam);
   case WM_SIZE:
      OnSize(LOWORD(lParam), HIWORD(lParam));
      break;
   case MSG_MOVESPLITTER:
      MoveSplitter(wParam);
      break;
   }

   return Window::ProcessMessage(message, wParam, lParam);
}

void SplitWindow::OnCreate()
{
   splitter = Splitter::Create(GetInstance(), *this);
}

LRESULT SplitWindow::OnCommand(WPARAM wParam, LPARAM lParam)
{
   int wmId = LOWORD(wParam);
   int wmEvent = HIWORD(wParam);
   switch (wmId) {
   case MSG_MOVESPLITTER:
      MoveSplitter(wParam);
      return 0;
   }
   return Window::ProcessMessage(WM_COMMAND, wParam, lParam);
}

void SplitWindow::OnSize(int width, int height) 
{
   this->width = width;
   this->height = height;

   int splitterX = CalculateSplitterX();
   int splitterSize = splitter->GetSize();

   splitter->MoveDelayPaint(splitterX, 0, splitterSize, this->height);
   leftWin->Move(0, 0, splitterX, this->height);
   rightWin->Move(splitterX + splitterSize, 0, this->width - splitterX - splitterSize, this->height);
   splitter->ForceRepaint();
}

int SplitWindow::CalculateSplitterX()
{
   int splitterX = (width * splitRatioPercentage) / 100;
   if (splitterX < 0)
      splitterX = 0;

   return splitterX;
}

void SplitWindow::MoveSplitter (int splitterX)
{
   splitRatioPercentage = CalculateSplitterPercentage(splitterX);
   OnSize(width, height);
}

int SplitWindow::CalculateSplitterPercentage(int splitterX)
{
   int newPercent = splitterX * 100 / width;
   if (newPercent < 0)
      newPercent = 0;
   else if (newPercent > 100)
      newPercent = 100;

   return newPercent;
}