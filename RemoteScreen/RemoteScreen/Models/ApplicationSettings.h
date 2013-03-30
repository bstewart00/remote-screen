#pragma once
#ifndef ApplicationSettings_H
#define ApplicationSettings_H

#include "Common/Observable.h"

class ApplicationSettingsListener
{
public:
   virtual void OnSettingsChanged() = 0;
};

class ApplicationSettings : public Common::Observable<ApplicationSettingsListener>
{
public:
   int someSetting() const
   {
      return someSetting_;
   }
   void someSetting(int value)
   {
      someSetting_ = value;
      NotifyListeners(&ApplicationSettingsListener::OnSettingsChanged);
   }

private:
   int someSetting_;
};

#endif