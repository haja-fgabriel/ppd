#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <functional>

namespace FileUtils {
    void ReadFile(
        const std::string& Filename,
        std::function<void(int)> InitialCallback,
        int NumProcesses,
        std::function<void(const std::vector<int>&, int, int)> Callback
    )
    {
        std::vector<int> number;
        std::ifstream f(Filename);
        std::string line;
        int n;
        f >> n >> line;

        n = ((n / NumProcesses) + 1) * NumProcesses;
        InitialCallback(n);

        number.clear();
        for (int i = 0; i < n; i++)
        {
            char c = '0';
            if (i < line.length()) c = line[i];

            number.push_back(c - '0');
            if ((i + 1) % (n / NumProcesses) == 0)
            {
                Callback(number, n, i-(i%(n/NumProcesses)));
            }
        }
    }

    void ReadFile(
        const std::string& Filename,
        std::vector<int>& Number1
    )
    {
        std::ifstream f(Filename);
        std::string line;
        int n;
        f >> n >> line;
        Number1.clear();
        for (auto c : line)
        {
            Number1.push_back(c - '0');
        }
    }

    void CreateNewFile(const std::string& Filename, size_t N, int Min, int Max)
    {
        std::ofstream g(Filename);
        std::random_device seeder;
        std::mt19937 generator(seeder());
        std::uniform_int_distribution<int> distribution(Min, Max);

        g << N << '\n';
        for (size_t i = 0; i < N; i++)
        {
            g << distribution(generator);
        }
        g << std::endl;

    }


    void Write(
        const std::string& Filename,
        const std::vector<int>& Number
    )
    {
        std::ofstream g(Filename);
        g << Number.size() << std::endl;
        for (auto v : Number)
            g << v;

        g << std::endl;
    }
};