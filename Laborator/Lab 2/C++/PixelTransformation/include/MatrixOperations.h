#pragma once

#include <iostream>
#include <fstream>

#include "Barrier.h"

#define MAX_HEIGHT (10000)
#define MAX_WIDTH (10000)

constexpr int NCoeff = 3;
constexpr int MCoeff = 3;

void 
ReadFile(
    const char* Filename,
    float Matrix[][MAX_WIDTH],
    int& N,
    int& M
)
{
    std::ifstream f(Filename);

    f >> N >> M;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            f >> Matrix[i][j];
}

void 
ReadFile(
    const char* Filename,
    float** &Matrix,
    int& N,
    int& M
)
{
    std::ifstream f(Filename);

    f >> N >> M;
    Matrix = new float*[N];
    for (int i = 0; i < N; i++)
    {
        Matrix[i] = new float[M];
        for (int j = 0; j < M; j++)
            f >> Matrix[i][j];
    }
}

template<typename T>
void
WriteToFile(
    const char* Filename,
    T Matrix,
    int N,
    int M
)
{
    std::ofstream g(Filename);
    g << N << ' ' << M << '\n';
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
            g << Matrix[i][j] << ' ';
        g << '\n';
    }
}

template<typename T>
void
TransformMatrix(
    T Input,
    T KeInput,
    int    N,
    int    M,
    int    KeN,
    int    KeM,
    int    start,
    int    end,
    Barrier* barrier
)
{
	int i = start/M, j = start%M;

    float* buffer = new float[end - start];

	for (int step = start; step < end; step++)
	{
        buffer[step-start] = 0.0;
        for (int ii = 0; ii < KeN; ii++)
        {
            for (int jj = 0; jj < KeM; jj++)
            {
                int k = i + ii - KeN/2;
                if (k < 0) k = 0; if (k >= N) k = N - 1;
                int l = j + jj - KeM/2;
                if (l < 0) l = 0; if (l >= M) l = M - 1;

#ifndef NO_DEBUG
                std::cout << "[DEBUG] (" << k << ", " << l << ")  (" << i << ", " << j << ")  (" << ii << ", " << jj << ") ";
                std::cout << Input[k][l] << ' ' << KeInput[ii + 1][jj + 1] << '\n';
#endif
                buffer[step-start] += Input[k][l] * KeInput[ii][jj];
            }
        }

        j++;
        if (j == M)
        {
            j = 0;
            i++;
        }
	}

    if (barrier)
        barrier->Wait();

    i = start / M, j = start % M;
    for (int step = start; step < end; step++)
    {
        Input[i][j] = buffer[step-start];
        j++;
        if (j == M)
        {
            j = 0;
            i++;
        }
    }

    delete[] buffer;
}
