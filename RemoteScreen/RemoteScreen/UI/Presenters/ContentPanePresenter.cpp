#include "stdafx.h"
#include <iostream>
#include <functional>
#include "ContentPanePresenter.h"

ContentPanePresenter::ContentPanePresenter(EventHub& eventHub) : eventHub(eventHub) 
{
   eventHub.Register(EventType::SelectedMonitorChanged, std::bind(&ContentPanePresenter::Refresh, this));
}

void ContentPanePresenter::SetView(ContentPane* view) 
{ 
   this->view = view; 
}

void ContentPanePresenter::Refresh()
{
   std::cout << "REFRESH" << std::endl;
}