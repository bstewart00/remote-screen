#pragma once
#ifndef SPLITTER_H
#define SPLITTER_H

#include <string>
#include <memory>
#include "../../Windows/Window.h"

namespace Splitter
{
   std::unique_ptr<Window> RegisterAndCreate(Window parent, HINSTANCE hInstance);
   const std::string WINDOW_CLASS_NAME = "Splitter";
   class Controller;
};

#endif