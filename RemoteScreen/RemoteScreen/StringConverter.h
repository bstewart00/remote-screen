#pragma once
#ifndef STRINGCONVERTER_H
#define STRINGCONVERTER_H

#include <string>
#include <memory>
#include <unordered_map>

class StringConverter
{
public:
   static std::shared_ptr<std::wstring> ToWide(const std::string& str);
   static std::string ToUtf8(const std::wstring& str);

private:
   static std::unordered_map<std::string, std::shared_ptr<std::wstring>> wide_cache;
};

#endif