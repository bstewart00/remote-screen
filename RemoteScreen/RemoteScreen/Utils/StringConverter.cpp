#include "../stdafx.h"
#include "StringConverter.h"
#include <boost/nowide/convert.hpp>

std::unique_ptr<std::wstring> StringConverter::ToWide(const std::string& str)
{
   std::unique_ptr<std::wstring> widened(new std::wstring(boost::nowide::widen(str)));
   return widened;
}

std::string StringConverter::ToUtf8(const std::wstring& str)
{
   return boost::nowide::narrow(str);
}