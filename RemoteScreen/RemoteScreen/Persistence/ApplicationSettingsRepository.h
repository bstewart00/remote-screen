#pragma once
#ifndef ApplicationSettingsRepository_H
#define ApplicationSettingsRepository_H

#include "../Models/ApplicationSettings.h"
#include "../Utils/WindowsDeleters.h"
#include <memory>
#include <boost/filesystem.hpp>

class ApplicationSettingsRepository
{
public:
   ApplicationSettings Get();
   void Save(const ApplicationSettings& settings);

private:
   boost::filesystem::path SettingsFilePath();

   void InitializeAppDataFolder();
   boost::filesystem::path appDataPath;
   boost::filesystem::path settingsFilePath;
};

#endif
