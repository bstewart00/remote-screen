#include "stdafx.h"
#include "EventHub.h"

#include <algorithm>

void EventHub::Publish(EventType eventType)
{
   auto result = listenerMap.find(eventType);
   if (result != listenerMap.end()) {
      std::vector<EventHandler> listeners = result->second;

      for (auto it = listeners.cbegin(); it != listeners.cend(); ++it) {
         (*it)();
      }
   }
}

void EventHub::Register(EventType eventType, EventHandler listener)
{
   auto it = listenerMap.find(eventType);
   if (it == listenerMap.end()) {
      std::vector<EventHandler> vec;
      vec.emplace_back(listener);
      listenerMap.insert(std::make_pair(eventType, vec));
   } else {
      it->second.push_back(listener);
   }
}