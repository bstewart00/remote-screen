#pragma once
#ifndef LOCALFREEDELETER_H
#define LOCALFREEDELETER_H

template<typename T>
struct LocalFreeDeleter
{
   void operator()(T*p){::LocalFree(p);}
};

#endif