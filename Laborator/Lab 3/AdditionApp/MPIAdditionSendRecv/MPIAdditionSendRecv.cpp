#include <iostream>
#include <algorithm>

#include "FileUtils.h"
#include "BigNumbers.h"
#include "Logging.h"

#include <mpi.h>

#include <ctime>


std::vector<int> number1;
std::vector<int> number2;
int currentProc;
int numProcesses;
int rank;
int saiz;
std::vector<int> chunk;

void SendSize(int Size)
{
    if (rank == 0)
    {
        saiz = Size;
        for (int i = 1; i < numProcesses; i++)
        {
            MPI_Request req;
            MPI_Isend(&Size, 1, MPI_INT, i, 1, MPI_COMM_WORLD, &req);
            MPI_Wait(&req, MPI_STATUS_IGNORE);
        }
    }
}

void SendToProcesses(const std::vector<int>& Chunk, int Size, int Index)
{
    if (rank == 0)
    {
        if (Index != 0)
        {
            MPI_Request req;
            MPI_Isend(Chunk.data() + Index, (Size / numProcesses), MPI_INT, Index / (Size / numProcesses), 2, MPI_COMM_WORLD, &req);
            MPI_Wait(&req, MPI_STATUS_IGNORE);
        }
        else
            chunk = Chunk;
    }
}

int main(int argc, char** argv)
{
    if (argc < 4)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file> <input2_file> <output_file> [--log-to-socket]\n";
        return 1;
    }

    int retVal = 0;
    int junk = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcesses);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    int size = 0;
    int carry = 0;
    int receivedCarry = 0;
    std::vector<int> add1;
    std::vector<int> add2;
    std::vector<int> output;

    clock_t start = clock();

    if (rank == 0)
    {
        std::vector<int> result;

        FileUtils::ReadFile(argv[1], SendSize, numProcesses, SendToProcesses);
        add1 = chunk;
        size = saiz;

        FileUtils::ReadFile(argv[2], SendSize, numProcesses, SendToProcesses);
        add2 = chunk;
        junk = saiz;
        
        size = max(size, junk);
        output.resize(size);
    }
    else
    {
        MPI_Request size1Req;
        MPI_Request size2Req;
        MPI_Request firstReq;
        MPI_Request secondReq;

        MPI_Irecv(&size, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &size1Req);

        MPI_Wait(&size1Req, MPI_STATUS_IGNORE);

        add1.resize(size/numProcesses);

        MPI_Irecv(&junk, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &size2Req);
        MPI_Wait(&size2Req, MPI_STATUS_IGNORE);


        add2.resize(junk/numProcesses);
        MPI_Irecv(add1.data(), size / numProcesses, MPI_INT, 0, 2, MPI_COMM_WORLD, &firstReq);
        MPI_Irecv(add2.data(), junk / numProcesses, MPI_INT, 0, 2, MPI_COMM_WORLD, &secondReq);

        size = max(size, junk);
        MPI_Wait(&firstReq, MPI_STATUS_IGNORE);
        MPI_Wait(&secondReq, MPI_STATUS_IGNORE);

    }

    MPI_Request carryReq;
    if (rank > 0)
    {
        MPI_Irecv(&receivedCarry, 1, MPI_INT, rank - 1, 1, MPI_COMM_WORLD, &carryReq);
        MPI_Wait(&carryReq, &status);
    }


    std::vector<double> clocks;
    std::vector<int> result;
    BigNumbers::Add(add1, add2, result, receivedCarry, &carry);

    if (rank < numProcesses - 1)
        MPI_Isend(&carry, 1, MPI_INT, rank + 1, 1, MPI_COMM_WORLD, &carryReq);


    clock_t end;
    double tim = 0.0;
    if (rank > 0)
    {
        MPI_Request resultReq;
        MPI_Isend(result.data(), size / numProcesses, MPI_INT, 0, 3, MPI_COMM_WORLD, &resultReq);
        end = clock();
        tim = 1.0 * (end - start) / CLOCKS_PER_SEC;
        MPI_Isend(&tim, 1, MPI_DOUBLE, 0, 4, MPI_COMM_WORLD, &resultReq);
    }
    else
    {
        std::vector<MPI_Request> resultReq;
        resultReq.resize(numProcesses);
        clocks.resize(numProcesses);
        
        memcpy(output.data(), result.data(), (size / numProcesses) * sizeof(int));

        for (int i = 1; i < numProcesses; i++)
            MPI_Irecv(output.data() + i * (size / numProcesses), size / numProcesses, MPI_INT, i, 3, MPI_COMM_WORLD, &resultReq[i]);

        for (int i = 1; i < numProcesses; i++)
            MPI_Wait(&resultReq[i], MPI_STATUS_IGNORE);

        end = clock();

        for (int i = 1; i < numProcesses; i++)
            MPI_Irecv(clocks.data() + i, 1, MPI_DOUBLE, i, 4, MPI_COMM_WORLD, &resultReq[i]);

        tim = 1.0 * (end - start) / CLOCKS_PER_SEC;

        for (int i = 1; i < numProcesses; i++)
        {
            MPI_Wait(&resultReq[i], MPI_STATUS_IGNORE);
            tim = max(clocks[i], tim);
        }

        std::cout << "[DEBUG] Time: " << tim << std::endl;

        if (argc >= 5 && strcmp(argv[4], "--log-to-socket") == 0)
            SendLog(tim);

        while (!output.empty() && !output.back())
            output.pop_back();
        FileUtils::Write(argv[3], output);
    }


    MPI_Finalize();
}