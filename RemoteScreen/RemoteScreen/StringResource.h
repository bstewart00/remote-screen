#pragma once
#ifndef STRINGRESOURCE_H
#define STRINGRESOURCE_H

#include "WindowsException.h"
#include <Windows.h>
#include <string>

class StringResource
{
   static const int MAX_LENGTH = 255;
public:
   StringResource (HINSTANCE hInst, int resId);

   operator std::string () { return str; }
private:
   std::string str;
};

#endif