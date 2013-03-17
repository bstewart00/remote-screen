#pragma once
#ifndef DeviceContext_H
#define DeviceContext_H

#include "WindowsException.h"
#include "Utils/StringConverter.h"
#include <Windows.h>
#include <string>

namespace Win32
{
   class DisplayDeviceContext
   {
   public:
      DisplayDeviceContext(const char* deviceName)
      {
         hDC = deviceName == nullptr
            ? CreateFromFullScreen(deviceName)
            : CreateFromSingleDevice(deviceName);

         if (!hDC)
            throw WindowsException("Failed to create compatible memory device context");
      }

      ~DisplayDeviceContext()
      {
         ::DeleteDC(hDC);
      }

      operator HDC() const
      {
         return hDC;
      }

   private:
      HDC CreateFromSingleDevice(const char* deviceName)
      {
         std::wstring wideName = StringConverter::ToWide(deviceName);
         HDC result = ::CreateDCW(wideName.c_str(), NULL, NULL, NULL);
         return result;
      }

      HDC CreateFromFullScreen(const char* deviceName)
      {
         return ::CreateDC(NULL, NULL, NULL, NULL);
      }

      HDC hDC;
   };

   class MemoryDeviceContext
   {
   public:
      MemoryDeviceContext(HDC hDC)
         : hDC(::CreateCompatibleDC(hDC))
      {
         if (!hDC)
            throw WindowsException("Failed to create compatible memory device context");
      }

      ~MemoryDeviceContext()
      {
         ::DeleteDC(hDC);
      }

      operator HDC() const
      {
         return hDC;
      }

   private:
      HDC hDC;
   };

   class WindowDeviceContext
   {
   public:
      WindowDeviceContext(HWND hWnd)
         : hWnd(hWnd), hDC(::GetDC(hWnd))
      {
         if (!hDC)
            throw WindowsException("Failed to create window device context");
      }

      ~WindowDeviceContext()
      {
         ::ReleaseDC(hWnd, hDC);
      }

      MemoryDeviceContext CreateCompatibleMemoryContext() const
      {
         return ::CreateCompatibleDC(hDC);
      }

      operator HDC() const
      {
         return hDC;
      }

   private:
      HDC hDC;
      HWND hWnd;
   };
}

#endif