#pragma once
#ifndef WindowsException_H
#define WindowsException_H

#include "Utils/WindowsDeleters.h"
#include <string>
#include <memory>
#include <Windows.h>

namespace Win32
{
   class WindowsException
   {
   public:
      WindowsException (const char* msg) : errorCode(::GetLastError()), message(msg) {}
      WindowsException (std::string msg) : errorCode(::GetLastError()), message(msg) {}

      DWORD GetErrorCode() const { return errorCode; }
      const char* GetMessage () const { return message.c_str(); }
      std::unique_ptr<WCHAR, LocalFreeDeleter> GetFormattedMessage () const;

   private:
      DWORD errorCode;
      std::string message;
   };
}

#endif