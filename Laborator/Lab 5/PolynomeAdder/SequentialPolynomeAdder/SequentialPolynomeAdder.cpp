#include <iostream>
#include <cstring>
#include <ctime>

#include "FileUtils.h"
#include "Lista.h"
#include "Logging.h"

using namespace std;

Lista l;

void AddToList(int Degree, double Coeff)
{
    l.adaugaInOrdine({ Degree, Coeff });
}

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        cerr << "Usage: " << argv[0] << " <num_input_files> <output_file> [--log-to-socket]" << endl;
        return 1;
    }

    clock_t begin = clock();
        
    int nInputFiles = atoi(argv[1]);
    for (int i = 1; i <= nInputFiles; i++)
    {
        char num[5];
        sprintf_s(num, "%03d", i);
        FileUtils::ReadFile("Polynome" + string(num) + ".txt", AddToList);
    }

    clock_t end = clock();
    double time = 1.0 * (end - begin) / CLOCKS_PER_SEC;

    cout << "[DEBUG] Time: " << time << endl;
    if (argc >= 4 && strcmp(argv[3], "--log-to-socket") == 0)
    {
        SendLog(time);
    }

    FileUtils::WriteFile(argv[2], l);
    
    return 0;
}