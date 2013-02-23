#include "../stdafx.h"
#include "StringResource.h"
#include "StringConverter.h"

StringResource::StringResource(int resId)
{
   wchar_t buffer[MAX_LENGTH + 1];

   if (!::LoadString (hInstance, resId, buffer, MAX_LENGTH + 1))
      throw WindowsException("Failed to load string");
   buf = StringConverter::ToUtf8(buffer);
}
HINSTANCE StringResource::hInstance = nullptr;

void StringResource::SetInstance(HINSTANCE hInst)
{
   hInstance = hInst;
}