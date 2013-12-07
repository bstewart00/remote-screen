#pragma once
#ifndef EventHub_H
#define EventHub_H

#include <functional>
#include <vector>
#include <map>

typedef std::function<void()>EventHandler;

enum class EventType
{
   SelectedMonitorChanged
};

class EventHub
{
public:
   EventHub() {}

   void Publish(EventType eventType);
   void Register(EventType eventType, EventHandler listener);

private:
   std::map<EventType, std::vector<EventHandler>> listenerMap;
};


#endif