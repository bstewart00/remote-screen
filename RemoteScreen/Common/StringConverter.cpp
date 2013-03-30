#include "StringConverter.h"
#include <boost/nowide/convert.hpp>

namespace Common
{
   std::wstring Common::StringConverter::ToWide(const std::string& str)
   {
      return boost::nowide::widen(str);
   }

   std::string Common::StringConverter::ToUtf8(const std::wstring& str)
   {
      return boost::nowide::narrow(str);
   }

}