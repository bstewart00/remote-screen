#pragma once
#ifndef WindowsDeleters_H
#define WindowsDeleters_H

#include <Windows.h>
#include <objbase.h>

namespace Win32
{
   struct LocalFreeDeleter
   {
      void operator()(void* p) const { ::LocalFree(p); }
   };
}

#endif