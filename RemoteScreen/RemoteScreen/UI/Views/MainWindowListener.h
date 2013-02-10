#pragma once
#ifndef MainWindowListener_H
#define MainWindowListener_H

class MainWindowListener
{
public:
   virtual void OnAboutDialog() const = 0;
   virtual void OnEditDialog() const = 0;
   virtual void OnExit() const = 0;
};

#endif