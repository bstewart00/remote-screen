#pragma once
#ifndef ImageSource_H
#define ImageSource_H

#include <Windows.h>

class ImageSource
{
public:
   virtual HBITMAP GetImage() = 0;
   virtual HBITMAP GetImage(int width, int height) = 0;
};

#endif