#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H

#include "Persistence\ApplicationSettingsProvider.h"
#include "Utils/StringConverter.h"
#include <Windows.h>
#include <memory>

class Application
{
public:
   Application(HINSTANCE hInstance, int nCmdShow);
   bool Initialize();
   int Run();

   HACCEL LoadAccelerators(std::string tableName) const
   {
      return ::LoadAccelerators(hInstance, StringConverter::ToWide(tableName).get()->c_str());
   }

private:
   std::unique_ptr<ApplicationSettingsProvider> settingsProvider;
   HINSTANCE hInstance;
   int nCmdShow;
};

#endif