#include "stdafx.h"
#include <iostream>
#include "ConfigPanePresenter.h"

ConfigPanePresenter::ConfigPanePresenter(EventHub& eventHub) : eventHub(eventHub) 
{
}

void ConfigPanePresenter::SetView(ConfigPane* view) 
{ 
   this->view = view; 
   view->AddListener(this);
}

void ConfigPanePresenter::OnMonitorSelected()
{
   eventHub.Publish(EventType::SelectedMonitorChanged);
}