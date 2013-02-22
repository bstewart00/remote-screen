#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H

#include "Persistence\ApplicationSettingsRepository.h"
#include "Utils/StringConverter.h"
#include <Windows.h>
#include <memory>

class Application
{
public:
   Application(HINSTANCE hInstance, int nCmdShow);
   int Run();

   HACCEL LoadAccelerators(std::string tableName) const
   {
      return ::LoadAccelerators(hInstance, StringConverter::ToWide(tableName).get()->c_str());
   }

private:
   HINSTANCE hInstance;
   int nCmdShow;
};

#endif