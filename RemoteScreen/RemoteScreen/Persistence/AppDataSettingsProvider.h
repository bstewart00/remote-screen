#pragma once
#ifndef AppDataSettingsProvider_H
#define AppDataSettingsProvider_H

#include "ApplicationSettingsProvider.h"
#include "../Utils/WindowsDeleters.h"
#include <memory>
#include <boost/filesystem.hpp>

class AppDataSettingsProvider : public ApplicationSettingsProvider
{
public:
   ApplicationSettings GetSettings();

private:
   void InitializeAppDataFolder();
   boost::filesystem::path appDataPath;
};

#endif
