#pragma once

#include <string>
#include <fstream>
#include <random>


namespace FileUtils
{
    template<typename T>
    static bool Compare(const std::string& A, const std::string& B)
    {
        size_t n, m;
        std::fstream f(A), f2(B);

        T x, y;

        f >> n;
        f2 >> m;
        
        if (n != m)
        {
            return false;
        }

        for (int i = 0; i < n; i++)
        {
            f >> x;
            f2 >> y;
            if (x != y)
            {
                return false;
            }
        }

        return true;
    }

    void CreateNewFile(const std::string& Filename, size_t Size, int Min, int Max)
    {
        std::ofstream g(Filename);
        std::random_device seeder;
        std::mt19937 generator(seeder());
        std::uniform_int_distribution<int> distribution(Min, Max);

        g << Size << std::endl;
        for (size_t i = 0; i < Size; i++)
        {
            g << distribution(generator) << ' ';
        }
        g << std::endl;
    }

};

