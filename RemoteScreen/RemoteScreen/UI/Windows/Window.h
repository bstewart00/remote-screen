#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include "WindowClass.h"
#include <Windows.h>
#include <string>
#include <functional>

class Window
{
public:
   Window(HWND hwnd);

   void Show(int nCmdShow);
   void Destroy();

   operator HWND() const { return hWnd; }
   inline void SetHWND(HWND hwnd) { hWnd = hwnd; }
   bool operator==(const HWND& hwnd) const { return hWnd == hwnd; }

   template <typename T>
   static inline T GetLongPtr(HWND hwnd, int index)
   {
      return reinterpret_cast<T>(::GetWindowLongPtr(hwnd, index));
   }

   template <typename T>
   inline T GetLongPtr(int index) const{ return this->GetLongPtr<T>(hWnd, index); }

   template <typename T>
   static inline void SetLongPtr(HWND hwnd, T value, int index)
   {
      ::SetWindowLongPtr(hwnd, index, reinterpret_cast<LONG_PTR>(hwnd, value));
   }

   template <typename T>
   inline void SetLongPtr(T value, int index) const { return this->SetLongPtr<T>(hWnd, value, index); }

   HINSTANCE GetInstance() const
   { 
      return GetLongPtr<HINSTANCE>(GWLP_HINSTANCE);		
   }

   HWND GetParent() const
   {
      return ::GetParent(hWnd);
   }

   void SetParent(HWND hwndParent) const
   {
      ::SetParent(hWnd, hwndParent);
   }

   void ClientToScreen(POINT & pt) const
   {
      ::ClientToScreen(hWnd, &pt);
   }

   LRESULT SendMessage(UINT msg, WPARAM wparam = 0, LPARAM lparam = 0) const
   {
      return ::SendMessage(hWnd, msg, wparam, lparam);
   }

   bool PostMessage(UINT msg, WPARAM wparam = 0, LPARAM lparam = 0) const
   {
      return ::PostMessage(hWnd, msg, wparam, lparam) != FALSE;
   }

   long SendChildMessage(int idChild, UINT msg, WPARAM wparam = 0, LPARAM lparam = 0) const
   {
      return ::SendDlgItemMessage(hWnd, idChild, msg, wparam, lparam);
   }

   void SetFocus() const
   { 
      ::SetFocus(hWnd); 
   }

   bool HasFocus() const
   {
      return ::GetFocus() == hWnd;
   }

   void CaptureMouse() const
   {
      ::SetCapture(hWnd);
   }

   static void ReleaseMouse()
   {
      ::ReleaseCapture();
   }

   bool HasCapture() const
   {
      return ::GetCapture() == hWnd;
   }

   int GetTextLength() const
   {
      return SendMessage(WM_GETTEXTLENGTH, 0, 0);
   }

   void GetString(wchar_t* buf, int len) const
   {
      SendMessage(WM_GETTEXT,(WPARAM) len,(LPARAM) buf);
   }

   void SetString(std::string text) const
   {
      std::wstring wideText = boost::nowide::widen(text);
      SendMessage(WM_SETTEXT, 0, reinterpret_cast<LPARAM>(wideText.c_str()));
   }

   void Select() const
   {
      SendMessage(EM_SETSEL, 0, -1);
   }

   void SetFont(HFONT hFont) const
   {
      BOOL fRedraw = TRUE;
      SendMessage(WM_SETFONT, (WPARAM)hFont, MAKELPARAM(fRedraw, 0));
   }
   void Show(int cmdShow = SW_SHOW) const
   { 
      ::ShowWindow(hWnd, cmdShow); 
   }

   void Hide() const
   { 
      ::ShowWindow(hWnd, SW_HIDE); 
   }

   void Update() const
   { 
      ::UpdateWindow(hWnd); 
   }

   void Move(int x, int y, int width, int height) const
   {
      ::MoveWindow(hWnd, x, y, width, height, TRUE);
   }

   void MoveDelayPaint(int x, int y, int width, int height) const
   {
      ::MoveWindow(hWnd, x, y, width, height, FALSE);
   }

   void Invalidate() const
   {
      ::InvalidateRect(hWnd, 0, TRUE);
   }

   void Invalidate(RECT const & rect) const
   {
      ::InvalidateRect(hWnd, &rect, TRUE);
   }

   void ForceRepaint() const
   {
      Invalidate();
      Update();
   }

   void Scroll(int xAmount, int yAmount) const
   {
      ::ScrollWindow(hWnd, xAmount, yAmount, 0, 0);
   }

   void Scroll(RECT & rect, int xAmount, int yAmount) const
   {
      ::ScrollWindow(hWnd, xAmount, yAmount, &rect, 0);
   }

   void GetClientRect(RECT & rect) const
   {
      ::GetClientRect(hWnd, &rect);
   }

   void GetWindowRect(RECT & rect) const
   {
      ::GetWindowRect(hWnd, &rect);
   }

   void AttachMenu(HMENU hMenu) const
   {
      if(!::SetMenu (hWnd, hMenu))
         throw WindowsException("Internal error: Cannot attach menu.");
   }

   void Enable() const
   {
      ::EnableWindow(hWnd, TRUE);
   }

   void Disable() const
   {
      ::EnableWindow(hWnd, FALSE);
   }

protected:
   void InvokeBoolFunc(std::function<BOOL(HWND)> func, std::string errorMessage);
   HWND hWnd;
};

#endif