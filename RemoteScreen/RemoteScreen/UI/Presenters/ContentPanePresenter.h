#pragma once
#ifndef ContentPanePresenter_H
#define ContentPanePresenter_H

#include "../Views/ContentPane.h"
#include "EventHub.h"

class ContentPanePresenter
{
public:
   ContentPanePresenter(EventHub& eventHub);
   void SetView(ContentPane* view);

private:
   void Refresh();

   ContentPane* view;
   EventHub& eventHub;
};

#endif