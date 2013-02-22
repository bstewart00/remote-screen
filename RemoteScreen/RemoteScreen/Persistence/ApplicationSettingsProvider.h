#pragma once
#ifndef ApplicationSettingsProvider_H
#define ApplicationSettingsProvider_H

#include "../Models/ApplicationSettings.h"

class ApplicationSettingsProvider
{
public:
   virtual ApplicationSettings GetSettings() = 0;
};

#endif