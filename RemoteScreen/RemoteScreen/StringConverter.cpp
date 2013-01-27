#include "StringConverter.h"
#include <boost/nowide/convert.hpp>

std::unordered_map<std::string, std::shared_ptr<std::wstring>> StringConverter::wide_cache;
std::shared_ptr<std::wstring> StringConverter::ToWide(const std::string& str)
{
   auto cached = wide_cache.find(str);
   if (cached != wide_cache.end()) {
      return cached->second;
   }   
   std::shared_ptr<std::wstring> widened(new std::wstring(boost::nowide::widen(str)));
   wide_cache.insert(std::make_pair(str, widened));

   return widened;
}

std::string StringConverter::ToUtf8(const std::wstring& str)
{
   return boost::nowide::narrow(str);
}