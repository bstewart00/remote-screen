#pragma once
#ifndef MonitorImageSource_H
#define MonitorImageSource_H

#include "ImageSource.h"
#include "Win32Framework/CustomWindow.h"

class MonitorImageSource : public ImageSource
{
public:
   MonitorImageSource() {}

   HBITMAP GetImage();
   HBITMAP GetImage(int width, int height);
};

#endif