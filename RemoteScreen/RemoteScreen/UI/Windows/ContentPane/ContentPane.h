#pragma once
#ifndef CONTENTPANE_H
#define CONTENTPANE_H

#include <memory>
#include <Windows.h>
#include "../Window.h"

class ContentPane : public Window
{
public:
   static std::unique_ptr<ContentPane> Create(const Window& parent, HINSTANCE hInstance);
private:
   ContentPane(HWND hwnd);
};

#endif