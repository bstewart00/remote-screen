#pragma once
struct EditDialogViewModel
{
   EditDialogViewModel(std::string text) : text(text) {}
   std::string text;

   bool IsNameOk () const { return text.length() < 5; }
};

