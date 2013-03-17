#include "stdafx.h"
#include "../resource.h"
#include "Win32Framework/Utils/StringResource.h"
#include "ApplicationSettingsRepository.h"
#include "Win32Framework/Utils/StringConverter.h"
#include <ShlObj.h>
#include <iostream>
#include <sstream>
#include <string>

void ApplicationSettingsRepository::InitializeAppDataFolder()
{
   wchar_t* path = nullptr;
   HRESULT result = ::SHGetKnownFolderPath(FOLDERID_RoamingAppData, KF_FLAG_CREATE, nullptr, &path);
   if (result == E_FAIL)
      throw std::runtime_error("Failed to get Roaming AppData directory.");

   appDataPath = Win32::StringConverter::ToUtf8(path);
   appDataPath /= Win32::StringResource(AppDataFolderName).str();

   ::CoTaskMemFree(path);
}

boost::filesystem::path ApplicationSettingsRepository::SettingsFilePath()
{
   if (appDataPath.empty())
      InitializeAppDataFolder();

   if (settingsFilePath.empty()) {
      Win32::StringResource fileName(AppDataFolderName);
      settingsFilePath = appDataPath / fileName.str();
   }

   return settingsFilePath;
}

ApplicationSettings ApplicationSettingsRepository::Get()
{
   ApplicationSettings settings;

   boost::filesystem::path settingsPath = SettingsFilePath();
   if (boost::filesystem::exists(settingsPath)) {
      int result = ::GetPrivateProfileInt(L"SomeSetting", L"test", -1, settingsPath.c_str());
      settings.someSetting(result);
   }

   return settings;
}

void ApplicationSettingsRepository::Save(const ApplicationSettings& settings)
{
   std::stringstream stream;
   stream << settings.someSetting();

   boost::filesystem::path settingsPath = SettingsFilePath();
   ::WritePrivateProfileString(L"SomeSetting", L"test", Win32::StringConverter::ToWide(stream.str()).c_str(), settingsPath.c_str());
}