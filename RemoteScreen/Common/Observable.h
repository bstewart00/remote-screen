#pragma once
#ifndef Observable_H
#define Observable_H

#include <vector>
#include <algorithm>
#include <functional>

namespace Common
{
   template<typename TListener>
   class Observable
   {
   public:
      void AddListener(TListener* listener)
      {
         listeners.push_back(listener);
      }

   protected:
      void NotifyListeners(void(TListener::*eventHandler)()) const
      {
         std::for_each(listeners.begin(), listeners.end(), std::bind(eventHandler, std::placeholders::_1));
      }

   private:
      std::vector<TListener*> listeners;
   };
}

#endif