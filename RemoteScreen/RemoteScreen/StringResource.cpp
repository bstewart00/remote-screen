#include "StringResource.h"

StringResource::StringResource (HINSTANCE hInst, int resId)
{
   wchar_t buffer[MAX_LENGTH + 1];

   if (!::LoadString (hInst, resId, buffer, MAX_LENGTH + 1))
      throw WindowsException("Failed to load string");
   str = boost::nowide::narrow(buffer);
}