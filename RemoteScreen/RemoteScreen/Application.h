#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H

#include "UI/Windows/WindowClass.h"
#include <Windows.h>

class Application
{
public:
   Application(HINSTANCE hInstance, int nCmdShow);
   bool Initialize();
   int Run();

private:
   bool RestoreExistingWindow(const WindowClass& windowClass);
   HINSTANCE hInstance;
   int nCmdShow;
};

#endif