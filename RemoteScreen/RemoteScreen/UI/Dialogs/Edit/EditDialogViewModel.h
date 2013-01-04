#pragma once
#ifndef EDITDIALOGVIEWMODEL_H
#define EDITDIALOGVIEWMODEL_H

struct EditDialogViewModel
{
   EditDialogViewModel(std::string text) : text(text) {}
   std::string text;

   bool IsNameOk () const { return text.length() < 5; }
};

#endif