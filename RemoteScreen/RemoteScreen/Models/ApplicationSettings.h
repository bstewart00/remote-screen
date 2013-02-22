#pragma once
#ifndef ApplicationSettings_H
#define ApplicationSettings_H

#include "../Observable.h"

class ApplicationSettingsListener
{
   virtual void OnSomeSettingChanged() const = 0;
};

class ApplicationSettings : public Observable<ApplicationSettingsListener>
{
public:
   int someSetting;
};

#endif