#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include <ctime>

using namespace std;

void Worker(int start, int end, int a[], int b[], int c[])
{
    for (int i = start; i < end; i++)
        c[i] = a[i] + b[i];

}   

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " <no_threads>\n";
        return 1;
    }
    clock_t tBegin, tEnd;
    tBegin = clock();

    vector<thread> threads;

    int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int b[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
    int c[10];

    int start = 0, end;
    int n = 10;
    int nThreads = atoi(argv[1]);
    int chunk = n / nThreads;
    int rest = n % nThreads;

    for (int i = 0; i < nThreads; i++)
    {
        end = start + chunk;
        if (rest > 0)
        {
            end++;
            rest--;
        }
        threads.push_back(thread(Worker, start, end, a, b, c));
        start = end;
    }

    for (int i = 0; i < nThreads; i++)
    {
        if (threads[i].joinable())
            threads[i].join();
    }

    for (int i = 0; i < n; i++)
    {
        cout << c[i] << ' ';
    }

    cout << '\n';

    tEnd = clock();

    cout << "Execution time: " << (double) (tEnd-tBegin) / CLOCKS_PER_SEC << " seconds." << endl;
    
}