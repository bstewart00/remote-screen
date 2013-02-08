#pragma once
#ifndef CONTENTPANE_H
#define CONTENTPANE_H

#include <memory>
#include "../WindowHandle.h"

class ContentPane : public WindowHandle
{
public:
   static std::unique_ptr<ContentPane> Create(const WindowHandle& parent, HINSTANCE hInstance);
private:
   ContentPane(HWND hwnd);
};

#endif