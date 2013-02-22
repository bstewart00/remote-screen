#include "../stdafx.h"
#include "AppDataSettingsProvider.h"
#include "../Utils/StringConverter.h"
#include <ShlObj.h>
#include <iostream>
#include <string>

void AppDataSettingsProvider::InitializeAppDataFolder()
{
   wchar_t* path = nullptr;
   HRESULT result = ::SHGetKnownFolderPath(FOLDERID_RoamingAppData, KF_FLAG_CREATE, nullptr, &path);
   if (result == E_FAIL)
      throw std::runtime_error("Failed to get Roaming AppData directory.");

   appDataPath = StringConverter::ToUtf8(path);
   appDataPath /= "RemoteScreen";
   ::CoTaskMemFree(path);
}

ApplicationSettings AppDataSettingsProvider::GetSettings()
{
   if (appDataPath.empty())
      InitializeAppDataFolder();

   ApplicationSettings settings;

   boost::filesystem::path settingsFilePath = appDataPath / "settings.ini";
   if (boost::filesystem::exists(settingsFilePath)) {
      int result = ::GetPrivateProfileInt(L"SomeSetting", L"test", -1, StringConverter::ToWide(settingsFilePath.string()).get()->c_str());
      settings.someSetting(result);
   }

   return settings;
}