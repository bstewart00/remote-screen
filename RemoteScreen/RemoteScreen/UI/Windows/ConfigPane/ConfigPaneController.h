#pragma once
#ifndef CONFIGPANECONTROLLER_H
#define CONFIGPANECONTROLLER_H

#include "../WindowController.h"

class ConfigPaneController : public WindowController
{
public:
   ConfigPaneController(Window window, CREATESTRUCT* createStruct);
   LRESULT ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);

private:
   LRESULT OnNotify(WPARAM wParam, LPARAM lParam);
};

#endif