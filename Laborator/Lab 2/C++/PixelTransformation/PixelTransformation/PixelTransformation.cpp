#include <iostream>
#include <ctime>
#include <cstring>

#include "Logging.h"

#define NO_DEBUG
#include "MatrixOperations.h"

float gInput[MAX_HEIGHT][MAX_WIDTH];
float gKernelInput[MAX_HEIGHT][MAX_WIDTH];
float gOutput[MAX_HEIGHT][MAX_WIDTH];

int main(int argc, char* argv[])
{
    int n, m;
    int keN, keM;
    clock_t tBegin;
    clock_t tEnd;

    if (argc < 4)
    {
        std::cerr << "Usage: " << argv[0] << " dynamic|static <input_file> <kernel_input_file> [--log-to-socket]\r\n";
        return 1;
    }

    if (strcmp(argv[1], "dynamic") == 0)
    {
        float** input;
        float** kernelInput;
        ReadFile(argv[2], input, n, m);
        ReadFile(argv[3], kernelInput, keN, keM);

        float** output = nullptr;
        output = new float*[n];
        for (int i = 0; i < n; i++)
        {
            output[i] = new float[m];
        }
        tBegin = clock();
        TransformMatrix(input, kernelInput, n, m, keN, keM, 0, n*m, nullptr);
        tEnd = clock();
        WriteToFile("output.txt", input, n, m);

        for (int i = 0; i < n; i++)
        {
            delete[] input[i];
            delete[] output[i];
        }
        delete input;
        delete output;
    }
    else if (strcmp(argv[1], "static") == 0)
    {
        ReadFile(argv[2], gInput, n, m);
        ReadFile(argv[3], gKernelInput, keN, keM);
        tBegin = clock();
        TransformMatrix(gInput, gKernelInput, n, m, keN, keM, 0, n*m, nullptr);
        tEnd = clock();
        WriteToFile("output.txt", gInput, n, m);
    }


    std::cout << "[DEBUG] Time: " << (double)(tEnd - tBegin) / CLOCKS_PER_SEC << std::endl;

    if (argc > 4 && strcmp(argv[4], "--log-to-socket") == 0)
    {
        SendLog((double)(tEnd - tBegin) / CLOCKS_PER_SEC);
    }
}