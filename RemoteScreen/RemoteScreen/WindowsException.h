#pragma once
#ifndef WINDOWSEXCEPTION_H
#define WINDOWSEXCEPTION_H

#include "LocalFreeDeleter.h"
#include <Windows.h>
#include <string>
#include <memory>

class WindowsException
{
public:
   WindowsException (const char* msg) : errorCode(::GetLastError()), message(msg) {}
   WindowsException (std::string msg) : errorCode(::GetLastError()), message(msg) {}

   DWORD GetErrorCode() const { return errorCode; }
   const char* GetMessage () const { return message.c_str(); }
   std::unique_ptr<WCHAR, LocalFreeDeleter<WCHAR>> GetFormattedMessage () const;

private:
   DWORD errorCode;
   std::string message;
};

#endif