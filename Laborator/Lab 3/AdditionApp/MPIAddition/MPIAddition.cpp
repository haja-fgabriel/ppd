#include <iostream>
#include <ctime>

#include "FileUtils.h"
#include "BigNumbers.h"
#include "Logging.h"

#include <mpi.h>

int main(int argc, char** argv)
{
    if (argc < 4)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file> <input2_file> <output_file> [--log-to-socket]\n";
        return 1;
    }

    int rank;
    int retVal = 0;
    int numProcesses;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcesses);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    std::vector<int> number1;
    std::vector<int> number2;

    int size = 0;
    int carry = 0;
    int receivedCarry = 0;
    std::vector<int> add1;
    std::vector<int> add2;
    std::vector<int> output;
    std::vector<double> times;
    times.resize(numProcesses);

    clock_t begin;
    clock_t end;
    begin = clock();

    if (rank == 0)
    {
        std::vector<int> result;

        FileUtils::ReadFile(argv[1], number1);
        FileUtils::ReadFile(argv[2], number2);

        if (number1.size() < number2.size())
            number1.resize(number2.size());
        else
            number2.resize(number1.size());


        size = number1.size();

        size = ((size / numProcesses) + 1) * numProcesses;
        number1.resize(size);
        number2.resize(size);
        output.resize(size);
    }
    retVal = MPI_Bcast(&size, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (retVal)
    {
        std::cerr << "MPI_Bcast failed with ret-val " << retVal << '\n';
        return 4;
    }

    add1.resize(size/numProcesses);
    add2.resize(size/numProcesses);

    retVal = MPI_Scatter(number1.data(), size/numProcesses, MPI_INT, add1.data(), size / numProcesses, MPI_INT, 0, MPI_COMM_WORLD);
    if (retVal)
    {
        std::cerr << "MPI_Scatter failed with ret-val " << retVal << '\n';
        return 2;
    }

    retVal = MPI_Scatter(number2.data(), size/numProcesses, MPI_INT, add2.data(), size / numProcesses, MPI_INT, 0, MPI_COMM_WORLD);
    if (retVal)
    {
        std::cerr << "MPI_Scatter failed with ret-val " << retVal << '\n';
        return 3;
    }

    MPI_Status status;

    if (rank > 0)
    {
        retVal = MPI_Recv(&receivedCarry, 1, MPI_INT, rank - 1, 1, MPI_COMM_WORLD, &status);
        if (retVal != 0)
        {
            std::cerr << "MPI_Recv failed with ret-val " << retVal << '\n';
            return 5;
        }
    }

    std::vector<int> result;
    BigNumbers::Add(add1, add2, result, receivedCarry, &carry);


    if (rank < numProcesses - 1)
        MPI_Send(&carry, 1, MPI_INT, rank + 1, 1, MPI_COMM_WORLD);

    MPI_Gather(result.data(), size / numProcesses, MPI_INT, output.data(), size / numProcesses, MPI_INT, 0, MPI_COMM_WORLD);

    end = clock();
    double tim = 1.0 * (end - begin) / CLOCKS_PER_SEC;
    MPI_Gather(&tim, 1, MPI_DOUBLE, times.data(), 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        for (auto t : times)
            tim = max(tim, t);

        std::cout << "[DEBUG] Time: " << tim << std::endl;

        if (argc >= 5 && strcmp(argv[4], "--log-to-socket") == 0)
            SendLog(tim);

        while (!output.empty() && !output.back())
            output.pop_back();

        FileUtils::Write(argv[3], output);
    }

    
    MPI_Finalize();
}