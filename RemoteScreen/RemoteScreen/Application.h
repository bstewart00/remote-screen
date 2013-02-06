#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H

#include "UI/Windows/WindowClass.h"
#include "Utils/StringConverter.h"
#include <Windows.h>

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
   HINSTANCE hInstance;
   int nCmdShow;
};

#endif