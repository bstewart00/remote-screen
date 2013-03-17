#include "stdafx.h"
#include "Win32Framework/WindowsException.h"
#include "Application.h"
#include <sstream>
#include <string>
#include <boost/format.hpp>
#include "Win32Framework/Utils/StringConverter.h"
#include <stdio.h>
#include <io.h>
#include <fcntl.h>

void OutOfMemoryHandler()
{
   throw std::runtime_error("Out of memory");
}

#ifdef _DEBUG
void OpenDebugConsole()
{
   ::AllocConsole();

   HANDLE handle_out = ::GetStdHandle(STD_OUTPUT_HANDLE);
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
   } catch (Win32::WindowsException e) {
      boost::format test = boost::format("Error: %1 Win32 Error %2: %3") % e.GetMessage() % e.GetErrorCode() % e.GetFormattedMessage();
      std::wstring message = Win32::StringConverter::ToWide(test.str());
      ::MessageBox (0, message.c_str(), L"Exception", MB_ICONEXCLAMATION | MB_OK);
   } catch(std::runtime_error e) {
      std::wstring message = Win32::StringConverter::ToWide(e.what());
      ::MessageBox(0, message.c_str(), L"Exception", MB_ICONEXCLAMATION | MB_OK);
   } catch (...) {
      ::MessageBox (0, L"Unknown Error", L"Exception", MB_ICONEXCLAMATION | MB_OK);
   }

   return 0;
}
