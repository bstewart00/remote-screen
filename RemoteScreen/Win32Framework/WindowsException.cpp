#include "WindowsException.h"

namespace Win32
{
   std::unique_ptr<WCHAR, LocalFreeDeleter> WindowsException::GetFormattedMessage () const
   {
      LPWSTR formattedText = nullptr;
      ::FormatMessageW(
         FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER |FORMAT_MESSAGE_IGNORE_INSERTS,
         NULL,
         errorCode,
         MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
         reinterpret_cast<LPWSTR>(&formattedText),
         0,
         NULL);

      return std::unique_ptr<WCHAR, LocalFreeDeleter>(formattedText);
   }
}