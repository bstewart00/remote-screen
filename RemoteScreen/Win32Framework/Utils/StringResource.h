#pragma once
#ifndef STRINGRESOURCE_H
#define STRINGRESOURCE_H

#include "../WindowsException.h"
#include <Windows.h>
#include <string>

class StringResource
{
public:
   static const int MAX_LENGTH = 255;

   StringResource (int resId);
   static void SetInstance(HINSTANCE hInst);

   operator std::string () const { return buf; }
   const std::string str() const { return buf; }
private:
   static HINSTANCE hInstance;

   std::string buf;
};

#endif