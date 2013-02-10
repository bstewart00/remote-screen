#pragma once
#ifndef MainWindowListener_H
#define MainWindowListener_H

class MainWindowListener
{
public:
   virtual void OnAbout() const = 0;
   virtual void OnEdit() const = 0;
   virtual void OnExit() const = 0;
};

#endif