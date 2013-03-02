#pragma once
#ifndef Bitmap_H
#define Bitmap_H

class Bitmap
{
public:
   Bitmap(char* data) : data(data) {}

private:
   char* data;
};

#endif