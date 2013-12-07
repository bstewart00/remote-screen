#pragma once
#ifndef ConfigPanePresenter_H
#define ConfigPanePresenter_H

#include "../Views/ConfigPane.h"
#include "EventHub.h"

class ConfigPanePresenter :  private ConfigPaneListener
{
public:
   ConfigPanePresenter(EventHub& eventHub);
   void SetView(ConfigPane* view);

private:
   void OnMonitorSelected();

   ConfigPane* view;
   EventHub& eventHub;
};

#endif