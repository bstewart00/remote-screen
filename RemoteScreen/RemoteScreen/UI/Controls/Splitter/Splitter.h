#pragma once
#ifndef SPLITTER_H
#define SPLITTER_H

#include <string>
#include "../../Windows/WindowHandle.h"

namespace Splitter
{
   WindowHandle RegisterAndCreate(WindowHandle parent, HINSTANCE hInstance);
   const std::string WINDOW_CLASS_NAME = "Splitter";
   class Controller;
};

#endif