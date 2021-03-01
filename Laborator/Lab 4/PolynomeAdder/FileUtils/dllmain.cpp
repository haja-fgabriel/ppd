// dllmain.cpp : Defines the entry point for the DLL application.
#include "framework.h"

#include "FileUtils.h"

#include "IteratorLP.h"

#include <iomanip>
#include <fstream>
#include <random>

using namespace std;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

void FileUtils::ReadFile(
    const std::string& Filename,
    const std::function<void(int, double)>& Callback
)
{
    std::ifstream f(Filename);
    int nMonomes;
    int degree;
    double coeff;
    f >> nMonomes;
    for (int i = 0; i < nMonomes; i++)
    {
        f >> degree >> coeff;
        Callback(degree, coeff);
    }
}

void FileUtils::WriteFile(
    const std::string& Filename,
    Lista& lista
)
{
    std::ofstream g(Filename);
    g << lista.dim() << endl;
    for (IteratorLP it = lista.prim(); it.valid(); it.urmator()) {
        if (it.element().Coefficient)
            g << it.element().Degree << ' ' << fixed << setprecision(4) << it.element().Coefficient << endl;
    }
}

void FileUtils::CreateNewFile(const std::string& Filename, int Degree, int NMonomes, double Min, double Max)
{
    std::ofstream g(Filename);
    std::random_device seeder;
    std::mt19937 generator(seeder());
    std::uniform_real_distribution<double> distribution(Min, Max);
    std::uniform_int_distribution<int> degreeDistribution(0, Degree - 1);
    std::bernoulli_distribution bernoulli(0.5);
    float sign[2] = { -1.0, 1.0 };

    g << NMonomes << std::endl;
    std::vector<bool> isTaken(Degree);

    int signIndex = bernoulli(generator);

    // We must have a coefficient of maximum degree, otherwise the polynome
    // will have a smaller degree
    g << Degree << ' ' << fixed << setprecision(4) << distribution(generator) * sign[signIndex] << std::endl;

    for (int i = 1; i < NMonomes; i++) {
        size_t deg;
        do {
            deg = degreeDistribution(generator);
        } while (isTaken[deg]);
        isTaken[deg] = true;

        int signIndex = bernoulli(generator);
        g << deg << ' ' << fixed << setprecision(4) << distribution(generator) * sign[signIndex] << std::endl;
    }
}

