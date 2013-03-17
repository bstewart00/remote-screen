#include "StringConverter.h"
#include <boost/nowide/convert.hpp>

namespace Win32
{
   std::wstring StringConverter::ToWide(const std::string& str)
   {
      return boost::nowide::widen(str);
   }

   std::string StringConverter::ToUtf8(const std::wstring& str)
   {
      return boost::nowide::narrow(str);
   }

}