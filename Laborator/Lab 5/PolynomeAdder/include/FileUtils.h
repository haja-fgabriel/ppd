#pragma once

#include <string>
#include <functional>
#include "Lista.h"
#include "Common.h"

class DLLEXPORT FileUtils
{
public:
    static void ReadFile( const std::string& Filename, const std::function<void(int, double)>& Callback);
    
    static void WriteFile(const std::string& Filename, Lista& lista);

    static void CreateNewFile(const std::string& Filename, int Degree, int NMonomes, double Min, double Max);
};

