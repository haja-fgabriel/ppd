#include <iostream>

#include <mpi.h>
#include <vector>

using namespace std;

int main(int argc, char** argv)
{
    int retVal = 0; 
    int numProcesses;
    int buf = 0;
    int rank;
    int $aaa = 1000;

    cout << $aaa << '\n';

    vector<int> nr1Local, nr2Local, resLocal;
    vector<int> nr1, nr2, rezultat;
    MPI_Status status;

    retVal = MPI_Init(&argc, &argv);
    if (retVal != MPI_SUCCESS)
    {
        cout << "MPI_Init failed with code " << retVal << "\n";
        MPI_Abort(MPI_COMM_WORLD, retVal);
    }

    retVal = MPI_Comm_size(MPI_COMM_WORLD, &numProcesses);
    if (retVal != MPI_SUCCESS)
    {
        cout << "MPI_Comm_size failed with code " << retVal << "\n";
        MPI_Abort(MPI_COMM_WORLD, retVal);
    }

    retVal = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (retVal != MPI_SUCCESS)
    {
        cout << "MPI_Comm_rank failed with code " << retVal << "\n";
        MPI_Abort(MPI_COMM_WORLD, retVal);
    }
    int nrElem = 10 / numProcesses;

    if (rank == 0)
    {
        vector<int> nr1, nr2, rezultat;
        for (int i = 0; i < 10; i++)
        {
            nr1.push_back(i);
            nr2.push_back(i + 2);
        }
        buf = 10;
        MPI_Send(&buf, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        cout << buf << '\n';
    }
    else
    {
        buf = 2;
        if (rank == 1)
            MPI_Recv(&buf, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        cout << buf << '\n';
    }
    MPI_Scatter(nr1.data(), nrElem, MPI_INT, nr1Local.data(), nrElem, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(nr2.data(), nrElem, MPI_INT, nr2Local.data(), nrElem, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = 0; i < nrElem; i++)
        resLocal[i] = nr1Local[i] + nr2Local[i];

    MPI_Gather(resLocal.data(), nrElem, MPI_INT, rezultat.data(), nrElem, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Finalize();
}