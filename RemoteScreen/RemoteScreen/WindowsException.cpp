#include "WindowsException.h"

std::unique_ptr<WCHAR, LocalFreeDeleter<WCHAR>> WindowsException::GetFormattedMessage () const
{
   LPWSTR formattedText = nullptr;
   ::FormatMessageW(
      FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER |FORMAT_MESSAGE_IGNORE_INSERTS,
      NULL,
      errorCode,
      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
      formattedText, 
      0,
      NULL);

   return std::unique_ptr<WCHAR, LocalFreeDeleter<WCHAR>>(formattedText);
}
