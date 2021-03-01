#include <iostream>
#include <vector>
#include <thread>
#include <ctime>
#include <cstring>

#include "Logging.h"

#define NO_DEBUG
#include "MatrixOperations.h"

using std::vector;
using std::thread;

float gInput[MAX_HEIGHT][MAX_WIDTH];
float gKernelInput[MAX_HEIGHT][MAX_WIDTH];
float gOutput[MAX_HEIGHT][MAX_WIDTH];

template<typename T>
void HaveFun(
    int NThreads,
    T Input,
    T KeInput,
    T Output,
    int N,
    int M,
    int KeN,
    int KeM
)
{
    int start = 0, end;
    int chunk = (N*M) / NThreads;
    int rest = (N*M) % NThreads;
    vector<thread> threads;

    for (int i = 0; i < NThreads; i++)
    {
        end = start + chunk;
        if (rest)
        {
            end++;
            rest--;
        }
        threads.push_back(thread(TransformMatrix<T>, Input, KeInput, Output, N, M, KeN, KeM, start, end));
        start = end;
    }
    for (int i = 0; i < NThreads; i++)
    {
        threads[i].join();
    }
}

int main(int argc, char* argv[])
{
    int n, m;
    int keN, keM;
    int nThreads;
    clock_t tBegin;
    clock_t tEnd;

    if (argc < 4)
    {
        std::cerr << "Usage: " << argv[0] << " dynamic|static <num_threads> <input_file> <kernel_input_file> [--log-to-socket]\r\n";
        return 1;
    }

    nThreads = atoi(argv[2]);

    if (strcmp(argv[1], "dynamic") == 0)
    {
        float** input;
        float** kernelInput;
        ReadFile(argv[3], input, n, m);
        ReadFile(argv[4], kernelInput, keN, keM);

        float** output = nullptr;
        output = new float*[n];
        for (int i = 0; i < n; i++)
        {
            output[i] = new float[m];
        }
        tBegin = clock();
        HaveFun(nThreads, input, kernelInput, output, n, m, keN, keM);
        tEnd = clock();
        //WriteToFile("output.txt", output, n, m);

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
        ReadFile(argv[3], gInput, n, m);
        ReadFile(argv[4], gKernelInput, keN, keM);
        
        tBegin = clock();
        HaveFun(nThreads, gInput, gKernelInput, gOutput, n, m, keN, keM);
        tEnd = clock();
        //WriteToFile("output.txt", gOutput, n, m);
    }

    std::cout << "[DEBUG] Time: " << (double)(tEnd - tBegin) / CLOCKS_PER_SEC << std::endl;

    if (argc > 5 && strcmp(argv[5], "--log-to-socket") == 0)
    {
        SendLog((double)(tEnd - tBegin) / CLOCKS_PER_SEC);
    }
}