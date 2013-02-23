#include "stdafx.h"
#include "WindowsException.h"
#include "Application.h"
#include <sstream>
#include <string>
#include <boost/format.hpp>
#include "Utils/StringConverter.h"
#include <stdio.h>
#include <io.h>
#include <fcntl.h>

void OutOfMemoryHandler()
{
   throw WindowsException("Out of memory");
}

#ifdef _DEBUG
void OpenDebugConsole()
{
   AllocConsole();

   HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
   int hCrt = _open_osfhandle((long) handle_out, _O_TEXT);
   FILE* hf_out = _fdopen(hCrt, "w");
   setvbuf(hf_out, NULL, _IONBF, 1);
   *stdout = *hf_out;
}
#endif

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
   std::set_new_handler(OutOfMemoryHandler);
#ifdef _DEBUG
   OpenDebugConsole();
#endif

   try {
      Application app(hInstance, nCmdShow);
      return app.Run();
   } catch (WindowsException e) {
      boost::format test = boost::format("Error: %1 Win32 Error %2: %3") % e.GetMessage() % e.GetErrorCode() % e.GetFormattedMessage();
      std::unique_ptr<std::wstring> message = StringConverter::ToWide(test.str());
      ::MessageBox (0, message.get()->c_str(), L"Exception", MB_ICONEXCLAMATION | MB_OK);
   } catch (...) {
      ::MessageBox (0, L"Unknown Error", L"Exception", MB_ICONEXCLAMATION | MB_OK);
   }

   return 0;
}