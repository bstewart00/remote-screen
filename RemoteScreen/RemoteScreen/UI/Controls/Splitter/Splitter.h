#pragma once
#ifndef SPLITTER_H
#define SPLITTER_H

#include <string>
#include <Windows.h>
#include "../../Windows/Window.h"

namespace Splitter
{
   Window RegisterAndCreate(Window parent, HINSTANCE hInstance);
   const std::string WINDOW_CLASS_NAME = "Splitter";
   class Controller;
};

#endif