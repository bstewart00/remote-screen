#pragma once
#ifndef STRINGCONVERTER_H
#define STRINGCONVERTER_H

#include <string>
#include <memory>

class StringConverter
{
public:
   static std::wstring ToWide(const std::string& str);
   static std::string ToUtf8(const std::wstring& str);
};

#endif