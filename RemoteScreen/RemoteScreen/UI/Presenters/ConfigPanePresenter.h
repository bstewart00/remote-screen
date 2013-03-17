#pragma once
#ifndef ConfigPanePresenter_H
#define ConfigPanePresenter_H

#include "../Views/ConfigPane.h"

class ConfigPanePresenter : private ConfigPaneListener
{
public:
   ConfigPanePresenter();

private:
   void OnMonitorSelected();
};

#endif